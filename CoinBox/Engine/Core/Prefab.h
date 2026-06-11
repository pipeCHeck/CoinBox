#pragma once

#include <functional>
#include <memory>

class GameObject;

class Prefab
{
public:
    using Factory = std::function<std::unique_ptr<GameObject>()>;

    Prefab() = default;
    explicit Prefab(Factory factory)
        : m_factory(factory)
    {
    }

    bool IsValid() const
    {
        return static_cast<bool>(m_factory);
    }

    std::unique_ptr<GameObject> Instantiate() const
    {
        return m_factory ? m_factory() : nullptr;
    }

private:
    Factory m_factory;
};
