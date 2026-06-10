#pragma once
#include "Component.h"

namespace WizardRaid
{
	class CameraController : public Component
	{
	public:
		void SetTargetObject(GameObject& target);

	protected:
		void Start() override;
		void Update(float deltaTime) override;

	private:
		GameObject* targetObject = nullptr;
	};
}