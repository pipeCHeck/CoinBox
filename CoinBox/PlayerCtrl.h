#pragma once
#include "Component.h"
#include "Animation.h"
#include "Prefab.h"

namespace WizardRaid {

	class PlayerCtrl : public Component {
	public:
		void SetPlayerBulletPrefab(const Prefab& prefab) { playerBulletPrefab = prefab; }

	protected:
		void Start() override;
		void Update(float deltaTime) override;
		Vector2 MoveTowards(const Vector2& current, const Vector2& target, float maxDelta);
	private:
		void FirePlayerBullet();

		Animator* animator;
		Prefab playerBulletPrefab;
		Vector2 m_velocity = Vector2(0.0f, 0.0f);
	};

}
