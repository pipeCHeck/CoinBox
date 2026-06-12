#pragma once
#include "Component.h"

namespace WizardRaid
{
	class UFOSuction : public Component
	{
	public:
		void SetSucking(bool sucking) { m_sucking = sucking; }
		bool IsSucking() const { return m_sucking; }

	private:
		bool m_sucking = false;
	};

}
