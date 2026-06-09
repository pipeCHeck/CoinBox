#include "TitleScene.h"

#include "SpriteRenderer.h"
#include "PlayerCtrl.h"

#include "Animation.h"
#include "Game/Characters/CoffiaCharacterFactory.h"
#include "SpriteRig.h"

#include <memory>

namespace WizardRaid
{
	void TitleScene::OnStart()
	{
		
		auto coffia = std::make_unique<GameObject>();
		coffia->SetName(L"Coffia");
		coffia->GetTransform().position = Vector2(640.0f, 520.0f);
		coffia->GetTransform().scale = Vector2(0.55f, 0.55f);

		SpriteRig* rig = coffia->AddComponent<SpriteRig>();
		CoffiaCharacterFactory::ConfigureRig(*rig);

		Animator* animator = coffia->AddComponent<Animator>();
		CoffiaCharacterFactory::ConfigureAnimator(*animator);


		coffia->AddComponent<PlayerCtrl>();

		AddObject(std::move(coffia));
		

		/*
		auto gear = std::make_unique<GameObject>();
		gear->AddComponent<SpriteRenderer>(L"tGear");
		gear->AddComponent<PlayerCtrl>();
		gear->GetTransform().scale = Vector2(0.2f, 0.2f);
		AddObject(std::move(gear));
		*/
	}
}