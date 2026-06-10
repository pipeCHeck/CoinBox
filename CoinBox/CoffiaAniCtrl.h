#pragma once
#include "Component.h"
#include "Animation.h"

namespace WizardRaid {

	class CoffiaAniCtrl : public Component {
	protected:
		void Start() override;
		void Update(float deltaTime) override;
	private:
		Animator* animator;
	};

}