#include "Scene.h"

#include "Camera.h"
#include "Physics2D.h"

#include <algorithm>

void Scene::Init()
{
    if (m_initialized)
    {
        return;
    }

    OnInit();

    for (const auto& object : m_objects)
    {
        object->Init();
    }

    m_initialized = true;
}

void Scene::Start()
{
    if (m_started)
    {
        return;
    }

    OnStart();

    for (const auto& object : m_objects)
    {
        object->Start();
    }
}

void Scene::Update(float deltaTime)
{
    Init();

    OnUpdate(deltaTime);

    for (const auto& object : m_objects)
    {
        object->Update(deltaTime);
    }

    Physics2D::Step(deltaTime);
}

void Scene::Render(ID2D1DeviceContext* d2dContext)
{
    Init();

    OnRender(d2dContext);

    D2D1_MATRIX_3X2_F previousTransform = D2D1::Matrix3x2F::Identity();
    bool appliedCamera = false;

    if (d2dContext)
    {
        for (const auto& object : m_objects)
        {
            Camera* camera = object->FindComponentInChildren<Camera>();
            if (!camera)
            {
                continue;
            }

            d2dContext->GetTransform(&previousTransform);
            d2dContext->SetTransform(camera->GetViewMatrix(d2dContext->GetSize()) * previousTransform);
            appliedCamera = true;
            break;
        }
    }

    std::vector<GameObject::RenderEntry> renderEntries;
    size_t sequence = 0;

    for (const auto& object : m_objects)
    {
        object->Init();
        object->CollectRenderEntries(renderEntries, sequence);
    }

    std::stable_sort(renderEntries.begin(), renderEntries.end(),
        [](const GameObject::RenderEntry& left, const GameObject::RenderEntry& right)
        {
            if (left.order != right.order)
            {
                return left.order < right.order;
            }

            return left.sequence < right.sequence;
        });

    for (const GameObject::RenderEntry& entry : renderEntries)
    {
        if (entry.component)
        {
            entry.component->Render(d2dContext);
        }
    }

    if (appliedCamera)
    {
        d2dContext->SetTransform(previousTransform);
    }
}

GameObject* Scene::AddObject(std::unique_ptr<GameObject> object)
{
    GameObject* rawObject = object.get();
    m_objects.push_back(std::move(object));

    if (rawObject && m_initialized)
    {
        rawObject->Init();
    }

    return rawObject;
}
