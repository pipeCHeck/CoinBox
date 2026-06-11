#pragma once

#include "Component.h"
#include "Vector2.h"

enum class Collider2DShape
{
    Box,
    Circle
};

class Collider2D : public Component
{
public:
    ~Collider2D() override;

    void Init() override;

    virtual Collider2DShape GetShape() const = 0;

    void SetEnabled(bool enabled) { m_enabled = enabled; }
    bool IsEnabled() const { return m_enabled; }
    bool IsActiveAndEnabled() const;

    void SetTrigger(bool trigger) { m_isTrigger = trigger; }
    bool IsTrigger() const { return m_isTrigger; }

    void SetOffset(const Vector2& offset) { m_offset = offset; }
    const Vector2& GetOffset() const { return m_offset; }
    Vector2 GetWorldCenter() const;

    float GetWorldRotation() const;
    Vector2 GetWorldScale() const;

private:
    bool m_registered = false;
    bool m_enabled = true;
    bool m_isTrigger = false;
    Vector2 m_offset = Vector2(0.0f, 0.0f);
};
