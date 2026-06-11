#pragma once

#include "Component.h"
#include "Transform.h"

#include <cstddef>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

// GameObject는 씬 안에 존재하는 하나의 대상입니다.
// GameObject 자체는 특별한 기능이 없고, Component를 붙여서 동작하게 만듭니다.
class GameObject
{
public:
    GameObject();
    virtual ~GameObject() = default;

    // unique_ptr로 소유권을 관리하므로 복사를 막습니다.
    GameObject(const GameObject&) = delete;
    GameObject& operator=(const GameObject&) = delete;

    bool IsActive() const { return m_active; }
    void SetActive(bool active) { m_active = active; }

    const std::wstring& GetName() const { return m_name; }
    void SetName(const std::wstring& name) { m_name = name; }

    GameObject* GetParent() const { return m_parent; }
    GameObject* AddChild(std::unique_ptr<GameObject> child);
    GameObject* FindChild(const std::wstring& name);
    const GameObject* FindChild(const std::wstring& name) const;

    // Transform도 Component지만, 모든 오브젝트가 기본으로 가지므로 편의 함수를 둡니다.
    // 컴포넌트에서는 GetOwner()->GetTransform()으로 위치/회전/크기를 읽고 바꿉니다.
    Transform& GetTransform() { return *m_transform; }
    const Transform& GetTransform() const { return *m_transform; }
    Transform& GetAniTransform() { return m_aniTransform; }
    const Transform& GetAniTransform() const { return m_aniTransform; }
    Transform GetWorldTransform() const;

    // Scene이 호출합니다. 직접 호출할 일은 거의 없습니다.
    void Init();
    void Start();
    void Update(float deltaTime);
    void Render(ID2D1DeviceContext* d2dContext);
    void DispatchCollisionEnter2D(const Collision2D& collision);
    void DispatchCollisionStay2D(const Collision2D& collision);
    void DispatchCollisionExit2D(const Collision2D& collision);

    struct RenderEntry
    {
        int order = 0;
        size_t sequence = 0;
        Component* component = nullptr;
    };

    void CollectRenderEntries(std::vector<RenderEntry>& entries, size_t& sequence);

    // 이 오브젝트에 새 컴포넌트를 붙입니다.
    // 사용 예: object->AddComponent<SpriteRenderer>(image);
    template <typename TComponent, typename... TArgs>
    TComponent* AddComponent(TArgs&&... args)
    {
        // 넣은 TComponent가 Component를 상속받은 경우에만 처리
        static_assert(std::is_base_of<Component, TComponent>::value, "TComponent must derive from Component.");

        auto component = std::make_unique<TComponent>(std::forward<TArgs>(args)...);
        TComponent* rawComponent = component.get();
        rawComponent->SetOwner(this);

        m_components.push_back(std::move(component));

        // 이미 Init이 끝난 오브젝트에 나중에 컴포넌트를 추가해도 바로 준비시킵니다.
        if (m_initialized)
        {
            rawComponent->Init();
        }

        return rawComponent;
    }

    // 이 오브젝트에 붙어 있는 특정 타입의 컴포넌트를 찾습니다.
    // 사용 예: auto renderer = object->GetComponent<SpriteRenderer>();
    template <typename TComponent>
    TComponent* GetComponent() const
    {
        static_assert(std::is_base_of<Component, TComponent>::value,
            "TComponent must derive from Component.");

        for (const auto& component : m_components)
        {
            if (auto found = dynamic_cast<TComponent*>(component.get()))
            {
                return found;
            }
        }

        return nullptr;
    }

    template <typename TComponent>
    TComponent* FindComponentInChildren() const
    {
        if (TComponent* component = GetComponent<TComponent>())
        {
            return component;
        }

        for (const auto& child : m_children)
        {
            if (TComponent* component = child->FindComponentInChildren<TComponent>())
            {
                return component;
            }
        }

        return nullptr;
    }

private:
    Transform* m_transform = nullptr;
    Transform m_aniTransform;
    GameObject* m_parent = nullptr;
    std::wstring m_name;
    bool m_active = true;
    bool m_initialized = false;
    bool m_started = false;
    std::vector<std::unique_ptr<Component>> m_components;
    std::vector<std::unique_ptr<GameObject>> m_children;
};
