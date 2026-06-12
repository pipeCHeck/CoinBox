#include "Game/Objects/UFOProjectile.h"

#include "GameObject.h"

namespace WizardRaid
{
    void UFOProjectile::Update(float deltaTime)
    {
        GameObject* owner = GetOwner();
        if (!owner)
        {
            return;
        }

        owner->GetTransform().position += m_direction * m_speed * deltaTime;

        m_elapsed += deltaTime;
        if (m_elapsed >= m_lifeTime)
        {
            owner->Destroy();
        }
    }

    void UFOProjectile::SetDirection(const Vector2& direction)
    {
        m_direction = direction;
        m_direction.Normalize();

        if (m_direction.Length() <= 0.0001f)
        {
            m_direction = Vector2(1.0f, 0.0f);
        }
    }
}
