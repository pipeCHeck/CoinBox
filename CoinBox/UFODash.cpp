#include "UFODash.h"

#include "GameObject.h"
#include "UFOStats.h"

namespace WizardRaid
{
	void UFODash::Start()
	{
		m_stats = GetOwner() ? GetOwner()->GetComponent<UFOStats>() : nullptr;
	}

	void UFODash::Update(float deltaTime)
	{
		if (m_remainingTime <= 0.0f)
		{
			return;
		}

		GameObject* owner = GetOwner();
		if (!owner)
		{
			return;
		}

		if (m_remainingTime > 0.0f)
		{
			const float timeRatio = m_duration > 0.0f ? m_remainingTime / m_duration : 0.0f;
			const float speedRatio = 0.35f + 0.65f * timeRatio * timeRatio;
			m_dashVelocity = m_dashDirection * (m_speed * speedRatio);

			m_remainingTime -= deltaTime;
			if (m_remainingTime < 0.0f)
			{
				m_remainingTime = 0.0f;
			}
		}
		else
		{
			m_dashVelocity = MoveTowards(
				m_dashVelocity,
				Vector2(0.0f, 0.0f),
				m_recoveryDeceleration * deltaTime);
		}

		owner->GetTransform().position += m_dashVelocity * deltaTime;
	}

	bool UFODash::TryDash(const Vector2& direction)
	{
		if (IsDashing())
		{
			return false;
		}

		if (m_stats && !m_stats->UseEnergy(m_energyCost))
		{
			return false;
		}

		m_dashDirection = direction;
		m_dashDirection.Normalize();

		if (m_dashDirection.Length() <= 0.0001f)
		{
			m_dashDirection = Vector2(1.0f, 0.0f);
		}

		m_remainingTime = m_duration;
		m_dashVelocity = m_dashDirection * m_speed;
		return true;
	}

	Vector2 UFODash::MoveTowards(const Vector2& current, const Vector2& target, float maxDelta) const
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
