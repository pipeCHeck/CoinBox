#include "UFOAttack.h"

#include "Game/Objects/UFOProjectile.h"
#include "GameObject.h"
#include "Scene.h"
#include "UFOStats.h"

#include <cmath>
#include <memory>

namespace WizardRaid
{
	void UFOAttack::Start()
	{
		m_stats = GetOwner() ? GetOwner()->GetComponent<UFOStats>() : nullptr;
	}

	void UFOAttack::Update(float deltaTime)
	{
		(void)deltaTime;
	}

	void UFOAttack::BeginPrimary(const Vector2& direction)
	{
		m_charging = true;
		m_chargeTime = 0.0f;
		m_chargeDirection = direction;
		m_chargeDirection.Normalize();

		if (m_chargeDirection.Length() <= 0.0001f)
		{
			m_chargeDirection = Vector2(1.0f, 0.0f);
		}
	}

	void UFOAttack::HoldPrimary(float deltaTime, const Vector2& direction)
	{
		if (!m_charging)
		{
			return;
		}

		m_chargeDirection = direction;
		m_chargeDirection.Normalize();

		if (m_chargeDirection.Length() <= 0.0001f)
		{
			m_chargeDirection = Vector2(1.0f, 0.0f);
		}

		const float energyCost = m_chargeEnergyPerSecond * deltaTime;
		if (!m_stats || m_stats->UseEnergy(energyCost))
		{
			m_chargeTime += deltaTime;
			if (m_chargeTime > m_maxChargeTime)
			{
				m_chargeTime = m_maxChargeTime;
			}
		}
	}

	void UFOAttack::ReleasePrimary(const Vector2& direction)
	{
		if (!m_charging)
		{
			return;
		}

		m_charging = false;

		Vector2 fireDirection = direction;
		fireDirection.Normalize();
		if (fireDirection.Length() <= 0.0001f)
		{
			fireDirection = m_chargeDirection;
		}

		const float chargeRatio = m_maxChargeTime > 0.0f ? m_chargeTime / m_maxChargeTime : 0.0f;
		FireProjectile(fireDirection, chargeRatio);
		m_chargeTime = 0.0f;
	}

	void UFOAttack::FireProjectile(const Vector2& direction, float chargeRatio)
	{
		GameObject* owner = GetOwner();
		if (!owner || !owner->GetScene() || !m_projectilePrefab.IsValid())
		{
			return;
		}

		Vector2 fireDirection = direction;
		fireDirection.Normalize();
		if (fireDirection.Length() <= 0.0001f)
		{
			fireDirection = Vector2(1.0f, 0.0f);
		}

		std::unique_ptr<GameObject> projectileObject = m_projectilePrefab.Instantiate();
		if (!projectileObject)
		{
			return;
		}

		if (chargeRatio < 0.0f)
		{
			chargeRatio = 0.0f;
		}
		if (chargeRatio > 1.0f)
		{
			chargeRatio = 1.0f;
		}

		const Transform ownerTransform = owner->GetWorldTransform();
		projectileObject->GetTransform().position = ownerTransform.position + fireDirection * 55.0f;
		projectileObject->GetTransform().rotation = std::atan2(fireDirection.y, fireDirection.x) * 180.0f / 3.1415926535f;

		if (UFOProjectile* projectile = projectileObject->GetComponent<UFOProjectile>())
		{
			projectile->SetDirection(fireDirection);
			projectile->SetSpeed(m_minProjectileSpeed + (m_maxProjectileSpeed - m_minProjectileSpeed) * chargeRatio);
			projectile->SetDamage(m_minProjectileDamage + (m_maxProjectileDamage - m_minProjectileDamage) * chargeRatio);
			projectile->SetLifeTime(5.0f);
		}

		owner->GetScene()->AddObject(std::move(projectileObject));
	}
}
