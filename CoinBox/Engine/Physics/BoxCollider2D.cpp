#include "BoxCollider2D.h"

#include <cmath>

BoxCollider2D::BoxCollider2D(const Vector2& size)
    : m_size(size)
{
}

Vector2 BoxCollider2D::GetWorldSize() const
{
    const Vector2 scale = GetWorldScale();
    return Vector2(std::fabs(m_size.x) * scale.x, std::fabs(m_size.y) * scale.y);
}

Vector2 BoxCollider2D::GetHalfSize() const
{
    return GetWorldSize() * 0.5f;
}

Vector2 BoxCollider2D::GetAxisX() const
{
    return RotateVector(Vector2(1.0f, 0.0f), GetWorldRotation());
}

Vector2 BoxCollider2D::GetAxisY() const
{
    return RotateVector(Vector2(0.0f, 1.0f), GetWorldRotation());
}
