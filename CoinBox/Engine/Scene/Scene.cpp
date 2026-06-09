#include "Scene.h"

void Scene::Init()
{
    if (m_initialized)
    {
        return;
    }

    // 씬이 자기 오브젝트를 만들 기회를 먼저 줍니다.
    OnInit();

    // 그 다음 씬 안의 모든 오브젝트와 컴포넌트를 초기화합니다.
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

    // 씬 자체 로직을 먼저 갱신합니다.
    OnUpdate(deltaTime);

    // 그 다음 씬 안의 오브젝트들이 자기 컴포넌트를 갱신합니다.
    for (const auto& object : m_objects)
    {
        object->Update(deltaTime);
    }
}

void Scene::Render(ID2D1DeviceContext* d2dContext)
{
    Init();

    // 씬 배경이나 씬 전용 렌더링이 필요하면 여기서 처리합니다.
    OnRender(d2dContext);

    // 그 다음 오브젝트들이 자기 렌더 컴포넌트를 그립니다.
    for (const auto& object : m_objects)
    {
        object->Render(d2dContext);
    }
}

GameObject* Scene::AddObject(std::unique_ptr<GameObject> object)
{
    GameObject* rawObject = object.get();
    m_objects.push_back(std::move(object));

    // 이미 실행 중인 씬에 오브젝트를 나중에 추가해도 바로 초기화합니다.
    if (rawObject && m_initialized)
    {
        rawObject->Init();
    }

    return rawObject;
}
