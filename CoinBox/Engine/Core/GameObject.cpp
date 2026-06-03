#include "GameObject.h"

GameObject::GameObject()
{
    // Transform은 모든 GameObject가 기본으로 가지는 필수 Component입니다.
    m_transform = AddComponent<Transform>();
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

    m_initialized = true;
}

void GameObject::Update(float deltaSeconds)
{
    if (!m_active)
    {
        return;
    }

    Init();

    for (const auto& component : m_components)
    {
        component->Update(deltaSeconds);
    }
}

void GameObject::Render(ID2D1DeviceContext* d2dContext)
{
    if (!m_active)
    {
        return;
    }

    Init();

    for (const auto& component : m_components)
    {
        component->Render(d2dContext);
    }
}
