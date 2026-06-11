#include "Collider2D.h"

#include "GameObject.h"
#include "Physics2D.h"

#include <cmath>

Collider2D::~Collider2D()
{
    if (m_registered)
    {
        Physics2D::UnregisterCollider(this);
    }
}

void Collider2D::Init()
{
    if (!m_registered)
    {
        Physics2D::RegisterCollider(this);
        m_registered = true;
    }
}

bool Collider2D::IsActiveAndEnabled() const
{
    GameObject* owner = GetOwner();
    return m_enabled && owner && owner->IsActive();
}

Vector2 Collider2D::GetWorldCenter() const
{
    GameObject* owner = GetOwner();
    if (!owner)
    {
        return m_offset;
    }

    const Transform worldTransform = owner->GetWorldTransform();
    const Vector2 scaledOffset = m_offset * worldTransform.scale;
    return worldTransform.position + RotateVector(scaledOffset, worldTransform.rotation);
}

float Collider2D::GetWorldRotation() const
{
    GameObject* owner = GetOwner();
    return owner ? owner->GetWorldTransform().rotation : 0.0f;
}

Vector2 Collider2D::GetWorldScale() const
{
    GameObject* owner = GetOwner();
    if (!owner)
    {
        return Vector2(1.0f, 1.0f);
    }

    const Vector2 scale = owner->GetWorldTransform().scale;
    return Vector2(std::fabs(scale.x), std::fabs(scale.y));
}
