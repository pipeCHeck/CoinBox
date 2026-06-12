#pragma once
#include "Component.h"
#include "Prefab.h"
#include "Vector2.h"

namespace WizardRaid
{
	class UFOStats;

	class UFOAttack : public Component
	{
	public:
		void Start() override;
		void Update(float deltaTime) override;

		void SetProjectilePrefab(const Prefab& prefab) { m_projectilePrefab = prefab; }
		void BeginPrimary(const Vector2& direction);
		void HoldPrimary(float deltaTime, const Vector2& direction);
		void ReleasePrimary(const Vector2& direction);

	private:
		void FireProjectile(const Vector2& direction, float chargeRatio);

		UFOStats* m_stats = nullptr;
		Prefab m_projectilePrefab;
		Vector2 m_chargeDirection = Vector2(1.0f, 0.0f);
		float m_chargeTime = 0.0f;
		float m_maxChargeTime = 1.2f;
		float m_chargeEnergyPerSecond = 16.0f;
		float m_minProjectileSpeed = 700.0f;
		float m_maxProjectileSpeed = 1400.0f;
		float m_minProjectileDamage = 8.0f;
		float m_maxProjectileDamage = 28.0f;
		bool m_charging = false;
	};

}
