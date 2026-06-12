#pragma once
#include "Component.h"

namespace WizardRaid
{
	class UFOStats : public Component
	{
	public:
		float GetHealth() const { return m_health; }
		float GetMaxHealth() const { return m_maxHealth; }
		void SetHealth(float health);
		void AddHealth(float amount);

		float GetEnergy() const { return m_energy; }
		float GetMaxEnergy() const { return m_maxEnergy; }
		void SetEnergy(float energy);
		void AddEnergy(float amount);
		bool UseEnergy(float amount);

		int GetGold() const { return m_gold; }
		void AddGold(int amount) { m_gold += amount; }

		bool HasKey() const { return m_hasKey; }
		void SetHasKey(bool hasKey) { m_hasKey = hasKey; }

	private:
		float Clamp(float value, float minValue, float maxValue) const;

		float m_health = 100.0f;
		float m_maxHealth = 100.0f;
		float m_energy = 100.0f;
		float m_maxEnergy = 100.0f;
		int m_gold = 0;
		bool m_hasKey = false;
	};

}
