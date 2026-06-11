#include "CircleCollider2D.h"

#include <algorithm>
#include <cmath>

CircleCollider2D::CircleCollider2D(float radius)
    : m_radius(radius)
{
}

float CircleCollider2D::GetWorldRadius() const
{
    const Vector2 scale = GetWorldScale();
    return std::fabs(m_radius) * (std::max)(scale.x, scale.y);
}
