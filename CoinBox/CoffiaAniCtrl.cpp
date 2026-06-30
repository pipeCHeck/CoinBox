#include "CoffiaAniCtrl.h"
#include "Input.h"
#include "Transform.h"
#include "GameObject.h"

namespace WizardRaid {

	void CoffiaAniCtrl::Start()
	{
		animator = GetOwner()->GetComponent<Animator>();
	}

	void CoffiaAniCtrl::Update(float deltaTime)
	{
		if (Input::IsKeyDown('Z')) {
			animator->Play(L"ChinRest_Clip", AnimationResetMode::Reset, [this]() {
				OnChinRestFinished();
			});
		}
		if (Input::IsKeyDown('X')) {
			animator->Play(L"Greeting_SmilingEyes_Clip");
		}
		if (Input::IsKeyDown('C')) {
			animator->Play(L"PoliteGreeting_Clip", AnimationResetMode::Reset);
		}
	}

	void CoffiaAniCtrl::OnChinRestFinished()
	{
		if (!animator) {
			return;
		}

		animator->Play(L"PoliteGreeting_Clip", AnimationResetMode::Reset);
	}
}
