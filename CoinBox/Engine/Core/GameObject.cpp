#include "GameObject.h"

#include <algorithm>

GameObject::GameObject()
{
    // 모든 GameObject는 기본 Transform 컴포넌트를 하나씩 가집니다.
    m_transform = AddComponent<Transform>();
}

GameObject* GameObject::AddChild(std::unique_ptr<GameObject> child)
{
    if (!child)
    {
        return nullptr;
    }

    GameObject* rawChild = child.get();
    rawChild->m_parent = this;
    rawChild->SetScene(m_scene);
    m_children.push_back(std::move(child));

    if (m_initialized)
    {
        rawChild->Init();
    }

    if (m_started)
    {
        rawChild->Start();
    }

    return rawChild;
}

void GameObject::SetScene(Scene* scene)
{
    m_scene = scene;

    for (const auto& child : m_children)
    {
        child->SetScene(scene);
    }
}

GameObject* GameObject::FindChild(const std::wstring& name)
{
    if (m_name == name)
    {
        return this;
    }

    for (const auto& child : m_children)
    {
        if (GameObject* found = child->FindChild(name))
        {
            return found;
        }
    }

    return nullptr;
}

const GameObject* GameObject::FindChild(const std::wstring& name) const
{
    if (m_name == name)
    {
        return this;
    }

    for (const auto& child : m_children)
    {
        if (const GameObject* found = child->FindChild(name))
        {
            return found;
        }
    }

    return nullptr;
}

Transform GameObject::GetWorldTransform() const
{
    const Transform localTransform = GetTransform() + GetAniTransform();

    if (!m_parent)
    {
        return localTransform;
    }

    const Transform parentTransform = m_parent->GetWorldTransform();
    Transform worldTransform;

    const Vector2 scaledPosition = localTransform.position * parentTransform.scale;

    worldTransform.position = parentTransform.position + RotateVector(scaledPosition, parentTransform.rotation);
    worldTransform.rotation = parentTransform.rotation + localTransform.rotation;
    worldTransform.scale = parentTransform.scale * localTransform.scale;

    return worldTransform;
}

void GameObject::Init()
{
    if (m_initialized)
    {
        return;
    }

    for (const auto& component : m_components)
    {
        component->Init();
    }

    for (const auto& child : m_children)
    {
        child->Init();
    }

    m_initialized = true;
}

void GameObject::Start()
{
    if (m_started)
    {
        return;
    }

    for (const auto& component : m_components)
    {
        component->Start();
    }

    for (const auto& child : m_children)
    {
        child->Start();
    }

    m_started = true;
}

void GameObject::Update(float deltaTime)
{
    if (!m_active || m_destroyed)
    {
        return;
    }

    Init();

    for (const auto& component : m_components)
    {
        component->Update(deltaTime);
    }

    for (const auto& child : m_children)
    {
        child->Update(deltaTime);
    }

    CleanupDestroyedChildren();
}

void GameObject::Render(ID2D1DeviceContext* d2dContext)
{
    if (!m_active || m_destroyed)
    {
        return;
    }

    Init();

    std::vector<RenderEntry> entries;
    size_t sequence = 0;
    CollectRenderEntries(entries, sequence);

    // 부모-자식 순서는 Transform 계산용이고, 실제 그리기 순서는 renderOrder로 따로 정렬합니다.
    // 그래서 얼굴은 몸통의 자식이어도 머리카락보다 앞/뒤에 원하는 순서로 배치할 수 있습니다.
    std::stable_sort(entries.begin(), entries.end(),
        [](const RenderEntry& left, const RenderEntry& right)
        {
            if (left.order != right.order)
            {
                return left.order < right.order;
            }

            return left.sequence < right.sequence;
        });

    for (const RenderEntry& entry : entries)
    {
        if (entry.component)
        {
            entry.component->Render(d2dContext);
        }
    }
}

void GameObject::DispatchCollisionEnter2D(const Collision2D& collision)
{
    if (!m_active || m_destroyed)
    {
        return;
    }

    for (const auto& component : m_components)
    {
        component->OnCollisionEnter2D(collision);
    }
}

void GameObject::DispatchCollisionStay2D(const Collision2D& collision)
{
    if (!m_active)
    {
        return;
    }

    for (const auto& component : m_components)
    {
        component->OnCollisionStay2D(collision);
    }
}

void GameObject::DispatchCollisionExit2D(const Collision2D& collision)
{
    for (const auto& component : m_components)
    {
        component->OnCollisionExit2D(collision);
    }
}

void GameObject::CollectRenderEntries(std::vector<RenderEntry>& entries, size_t& sequence)
{
    if (!m_active)
    {
        return;
    }

    for (const auto& component : m_components)
    {
        // renderOrder가 같은 컴포넌트끼리는 추가된 순서를 유지합니다.
        entries.push_back(RenderEntry{ component->GetRenderOrder(), sequence++, component.get() });
    }

    for (const auto& child : m_children)
    {
        child->CollectRenderEntries(entries, sequence);
    }
}

void GameObject::CleanupDestroyedChildren()
{
    m_children.erase(
        std::remove_if(
            m_children.begin(),
            m_children.end(),
            [](const std::unique_ptr<GameObject>& child)
            {
                return child && child->IsDestroyed();
            }),
        m_children.end());
}
