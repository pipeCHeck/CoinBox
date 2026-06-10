#include "TitleScene.h"

#include "SpriteRenderer.h"
#include "PlayerCtrl.h"
#include "CoffiaAniCtrl.h"

#include "Animation.h"
#include "Camera.h"
#include "Game/Characters/CoffiaCharacterFactory.h"
#include "SpriteRig.h"
#include "CameraController.h"

#include <memory>

namespace WizardRaid
{
	void TitleScene::OnStart()
	{
		auto camera = std::make_unique<GameObject>();
		camera->SetName(L"MainCamera");
		camera->GetTransform().position = Vector2(640.0f, 360.0f);
		camera->AddComponent<Camera>();
		camera->AddComponent<CameraController>();

		auto coffia = std::make_unique<GameObject>();
		coffia->SetName(L"Coffia");
		coffia->GetTransform().position = Vector2(640.0f, 520.0f);
		coffia->GetTransform().scale = Vector2(0.55f, 0.55f);
		coffia->AddComponent<PlayerCtrl>();
		coffia->AddComponent<CoffiaAniCtrl>();

		auto table = std::make_unique<GameObject>();
		table->SetName(L"Table");
		table->GetTransform().position = Vector2(640.0f, 360.0f);
		table->AddComponent<SpriteRenderer>(L"tTable");
		table->GetComponent<SpriteRenderer>()->SetRenderOrder(200);

		auto background = std::make_unique<GameObject>();
		background->SetName(L"Background");
		background->GetTransform().position = Vector2(640.0f, 360.0f);
		background->AddComponent<SpriteRenderer>(L"tBackgorund_Shop");
		background->GetComponent<SpriteRenderer>()->SetRenderOrder(-1000);
		


		SpriteRig* rig = coffia->AddComponent<SpriteRig>();
		CoffiaCharacterFactory::ConfigureRig(*rig);

		Animator* animator = coffia->AddComponent<Animator>();
		CoffiaCharacterFactory::ConfigureAnimator(*animator);

		camera->GetComponent<CameraController>()->SetTargetObject(*coffia);

		AddObject(std::move(camera));
		AddObject(std::move(coffia));
		AddObject(std::move(background));
		AddObject(std::move(table));

		/*
		auto gear = std::make_unique<GameObject>();
		gear->AddComponent<SpriteRenderer>(L"tGear");
		gear->AddComponent<PlayerCtrl>();
		gear->GetTransform().scale = Vector2(0.2f, 0.2f);
		AddObject(std::move(gear));
		*/
	}
}
