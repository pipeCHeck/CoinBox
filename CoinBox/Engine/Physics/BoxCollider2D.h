#pragma once

#include "Collider2D.h"

class BoxCollider2D : public Collider2D
{
public:
    BoxCollider2D() = default;
    explicit BoxCollider2D(const Vector2& size);

    Collider2DShape GetShape() const override { return Collider2DShape::Box; }

    void SetSize(const Vector2& size) { m_size = size; }
    const Vector2& GetSize() const { return m_size; }
    Vector2 GetWorldSize() const;
    Vector2 GetHalfSize() const;

    Vector2 GetAxisX() const;
    Vector2 GetAxisY() const;

private:
    Vector2 m_size = Vector2(1.0f, 1.0f);
};
