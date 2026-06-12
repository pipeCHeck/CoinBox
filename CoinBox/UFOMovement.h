#pragma once
#include "Component.h"

namespace WizardRaid
{
	class UFOMovement : public Component
	{
	public:
		void SetMoveInput(const Vector2& input);
		const Vector2& GetVelocity() const { return m_velocity; }

		void Update(float deltaTime) override;

	private:
		Vector2 MoveTowards(const Vector2& current, const Vector2& target, float maxDelta) const;

		Vector2 m_moveInput = Vector2(0.0f, 0.0f);
		Vector2 m_velocity = Vector2(0.0f, 0.0f);
		float m_speed = 500.0f;
		float m_acceleration = 5200.0f;
		float m_deceleration = 3600.0f;
	};

}
