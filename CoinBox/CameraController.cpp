#include "CameraController.h"
#include "Input.h"
#include "GameObject.h"

#include <Windows.h>

namespace WizardRaid
{
	void CameraController::SetTargetObject(GameObject& target)
	{
		targetObject = &target;
	}

	void CameraController::Start()
	{

	}

	void CameraController::Update(float deltaTime)
	{
		if (targetObject == nullptr)
			return;

		Vector2 centerPos = (Input::GetMousePositionInScreenCenter()/10) + targetObject->GetTransform().position;
		Transform& transform = GetOwner()->GetTransform();

		Vector2 testPos = Input::GetMousePositionInScreenCenter(); 
		
		wchar_t buffer[128];
		swprintf_s(buffer, L"x: %.2f y: %.2f\n", testPos.x, testPos.y);
		OutputDebugStringW(buffer);


		transform.position = SmoothFollow(transform.position, centerPos, 10.0f, deltaTime);
	}
}
