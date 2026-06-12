#include "UFOMovement.h"

#include "GameObject.h"

namespace WizardRaid
{
	void UFOMovement::SetMoveInput(const Vector2& input)
	{
		m_moveInput = input;
		m_moveInput.Normalize();
	}

	void UFOMovement::Update(float deltaTime)
	{
		GameObject* owner = GetOwner();
		if (!owner)
		{
			return;
		}

		const bool hasMoveInput = m_moveInput.Length() > 0.0f;
		const Vector2 targetVelocity = hasMoveInput
			? m_moveInput * m_speed
			: Vector2(0.0f, 0.0f);
		const float moveRate = hasMoveInput ? m_acceleration : m_deceleration;

		m_velocity = MoveTowards(m_velocity, targetVelocity, moveRate * deltaTime);
		owner->GetTransform().position += m_velocity * deltaTime;
	}

	Vector2 UFOMovement::MoveTowards(const Vector2& current, const Vector2& target, float maxDelta) const
	{
		const Vector2 delta = target - current;
		const float distance = delta.Length();

		if (distance <= maxDelta || distance <= 0.0001f)
		{
			return target;
		}

		return current + (delta / distance) * maxDelta;
	}
}
