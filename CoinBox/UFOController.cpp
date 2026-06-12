#include "UFOController.h"

#include "GameObject.h"
#include "Input.h"
#include "UFOAttack.h"
#include "UFOSuction.h"
#include "UFODash.h"
#include "UFOMovement.h"
#include "UFOStats.h"
#include "Screen.h"

namespace WizardRaid
{
	void UFOController::Start()
	{
		GameObject* owner = GetOwner();

		m_attack = owner->GetComponent<UFOAttack>();
		m_suction = owner->GetComponent<UFOSuction>();
		m_dash = owner->GetComponent<UFODash>();
		m_movement = owner->GetComponent<UFOMovement>();
		m_stats = owner->GetComponent<UFOStats>();
	}

	void UFOController::Update(float deltaTime)
	{
		Vector2 moveInput = Vector2(0.0f, 0.0f);

		if (Input::IsKey('A'))
		{
			moveInput.x -= 1.0f;
		}
		if (Input::IsKey('D'))
		{
			moveInput.x += 1.0f;
		}
		if (Input::IsKey('W'))
		{
			moveInput.y -= 1.0f;
		}
		if (Input::IsKey('S'))
		{
			moveInput.y += 1.0f;
		}

		moveInput.Normalize();

		if (m_movement)
		{
			m_movement->SetMoveInput(moveInput);
		}

		if (Input::IsKeyDown(VK_SPACE) && m_dash)
		{
			m_dash->TryDash(moveInput);
		}

		Vector2 attackDirection = Input::GetMousePositionInScreen() - Screen::GetCenter();
		attackDirection.Normalize();
		if (attackDirection.Length() <= 0.0001f)
		{
			attackDirection = Vector2(1.0f, 0.0f);
		}

		if (m_attack)
		{
			if (Input::IsMouseDown(MouseButton::Left))
			{
				m_attack->BeginPrimary(attackDirection);
			}

			if (Input::IsMouse(MouseButton::Left))
			{
				m_attack->HoldPrimary(deltaTime, attackDirection);
			}

			if (Input::IsMouseUp(MouseButton::Left))
			{
				m_attack->ReleasePrimary(attackDirection);
			}
		}

		if (m_suction)
		{
			m_suction->SetSucking(Input::IsMouse(MouseButton::Right));
		}
	}
}
