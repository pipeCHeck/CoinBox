#pragma once
#include "Component.h"

namespace WizardRaid {

	class PlayerCtrl : public Component {
	protected:
		void Update(float deltaTime) override;
	};

}