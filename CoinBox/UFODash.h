#pragma once
#include "Component.h"

namespace WizardRaid
{
	class UFOStats;

	class UFODash : public Component
	{
	public:
		void Start() override;
		void Update(float deltaTime) override;

		bool TryDash(const Vector2& direction);
		bool IsDashing() const { return m_remainingTime > 0.0f || m_dashVelocity.Length() > 1.0f; }

	private:
		Vector2 MoveTowards(const Vector2& current, const Vector2& target, float maxDelta) const;

		UFOStats* m_stats = nullptr;
		Vector2 m_dashDirection = Vector2(1.0f, 0.0f);
		Vector2 m_dashVelocity = Vector2(0.0f, 0.0f);
		float m_speed = 1400.0f;
		float m_duration = 0.16f;
		float m_remainingTime = 0.0f;
		float m_recoveryDeceleration = 5600.0f;
		float m_energyCost = 18.0f;
	};

}
