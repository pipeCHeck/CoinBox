#include "PlayerCtrl.h"
#include "Input.h"
#include "Transform.h"
#include "GameObject.h"

namespace WizardRaid {

	void PlayerCtrl::Update(float deltaTime)
	{
		Transform& transform = GetOwner()->GetTransform();
		const float speed = 320.0f;

		if (Input::IsKey(VK_LEFT)) {
			transform.position.x -= speed * deltaTime;
		}
		if (Input::IsKey(VK_RIGHT)) {
			transform.position.x += speed * deltaTime;
		}
		if (Input::IsKey(VK_DOWN)) {
			transform.position.y += speed * deltaTime;
		}
		if (Input::IsKey(VK_UP)) {
			transform.position.y -= speed * deltaTime;
		}
	}
}