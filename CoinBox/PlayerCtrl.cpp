#include "PlayerCtrl.h"
#include "Input.h"
#include "Transform.h"
#include "GameObject.h"
#include "Game/Objects/PlayerBullet.h"
#include "Scene.h"
#include "Screen.h"

#include <cmath>
#include <memory>

namespace WizardRaid 
{

	void PlayerCtrl::Start() 
	{
		animator = GetOwner()->GetComponent<Animator>();
	}

	void PlayerCtrl::Update(float deltaTime)
	{
		Transform& transform = GetOwner()->GetTransform();
		const float speed = 500.0f;
		const float acceleration = 5200.0f;
		const float deceleration = 3600.0f;
		const float startNudgeDistance = 8.0f;

		Vector2 inputDir = Vector2(0, 0);

		if (Input::IsKey('A')) {
			inputDir.x -= 1;
		}
		if (Input::IsKey('D')) {
			inputDir.x += 1;
		}
		if (Input::IsKey('S')) {
			inputDir.y += 1;
		}
		if (Input::IsKey('W')) {
			inputDir.y -= 1;
		}

		inputDir.Normalize();

		const bool hasMoveInput = inputDir.Length() > 0.0f;

		const Vector2 targetVelocity = hasMoveInput
			? inputDir * speed
			: Vector2(0.0f, 0.0f);
		const float moveRate = hasMoveInput ? acceleration : deceleration;

		m_velocity = MoveTowards(m_velocity, targetVelocity, moveRate * deltaTime);
		transform.position += m_velocity * deltaTime;

		if (Input::IsKeyDown('Z')) {
			animator->Play(L"ChinRest_Clip");
		}
		if (Input::IsKeyDown('X')) {
			animator->Play(L"Greeting_SmilingEyes_Clip");
		}

		if (Input::IsMouseDown(MouseButton::Left)) {
			FirePlayerBullet();
		}
	}

	Vector2 PlayerCtrl::MoveTowards(const Vector2& current, const Vector2& target, float maxDelta)
	{
		const Vector2 delta = target - current;
		const float distance = delta.Length();

		if (distance <= maxDelta || distance <= 0.0001f)
		{
			return target;
		}

		return current + (delta / distance) * maxDelta;
	}

	void PlayerCtrl::FirePlayerBullet()
	{
		GameObject* owner = GetOwner();
		if (!owner || !owner->GetScene() || !playerBulletPrefab.IsValid())
		{
			return;
		}

		Vector2 direction = Input::GetMousePositionInScreen() - Screen::GetCenter();
		direction.Normalize();

		if (direction.Length() <= 0.0001f)
		{
			direction = Vector2(1.0f, 0.0f);
		}

		std::unique_ptr<GameObject> bulletObject = playerBulletPrefab.Instantiate();
		if (!bulletObject)
		{
			return;
		}

		const Transform ownerTransform = owner->GetWorldTransform();
		bulletObject->GetTransform().position = ownerTransform.position + direction * 55.0f;
		bulletObject->GetTransform().rotation = std::atan2(direction.y, direction.x) * 180.0f / 3.1415926535f;

		if (PlayerBullet* bullet = bulletObject->GetComponent<PlayerBullet>())
		{
			bullet->SetDirection(direction);
		}

		owner->GetScene()->AddObject(std::move(bulletObject));
	}
}
