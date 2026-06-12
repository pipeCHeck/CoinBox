#include "UFOStats.h"

namespace WizardRaid
{
	void UFOStats::SetHealth(float health)
	{
		m_health = Clamp(health, 0.0f, m_maxHealth);
	}

	void UFOStats::AddHealth(float amount)
	{
		SetHealth(m_health + amount);
	}

	void UFOStats::SetEnergy(float energy)
	{
		m_energy = Clamp(energy, 0.0f, m_maxEnergy);
	}

	void UFOStats::AddEnergy(float amount)
	{
		SetEnergy(m_energy + amount);
	}

	bool UFOStats::UseEnergy(float amount)
	{
		if (amount <= 0.0f)
		{
			return true;
		}

		if (m_energy < amount)
		{
			return false;
		}

		m_energy -= amount;
		return true;
	}

	float UFOStats::Clamp(float value, float minValue, float maxValue) const
	{
		if (value < minValue)
		{
			return minValue;
		}

		if (value > maxValue)
		{
			return maxValue;
		}

		return value;
	}
}
