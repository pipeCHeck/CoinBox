#pragma once

#include "Collider2D.h"

class CircleCollider2D : public Collider2D
{
public:
    CircleCollider2D() = default;
    explicit CircleCollider2D(float radius);

    Collider2DShape GetShape() const override { return Collider2DShape::Circle; }

    void SetRadius(float radius) { m_radius = radius; }
    float GetRadius() const { return m_radius; }
    float GetWorldRadius() const;

private:
    float m_radius = 0.5f;
};
