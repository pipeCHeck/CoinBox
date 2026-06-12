#pragma once

#include "Component.h"
#include "Vector2.h"

namespace WizardRaid
{
    class PlayerBullet : public Component
    {
    public:
        void Update(float deltaTime) override;

        void SetDirection(const Vector2& direction);
        const Vector2& GetDirection() const { return m_direction; }

        void SetSpeed(float speed) { m_speed = speed; }
        float GetSpeed() const { return m_speed; }

        void SetLifeTime(float lifeTime) { m_lifeTime = lifeTime; }
        float GetLifeTime() const { return m_lifeTime; }

    private:
        Vector2 m_direction = Vector2(1.0f, 0.0f);
        float m_speed = 900.0f;
        float m_lifeTime = 5.0f;
        float m_elapsed = 0.0f;
    };
}
