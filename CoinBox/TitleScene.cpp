#include "TitleScene.h"

#include "SpriteRenderer.h"

#include "Camera.h"
#include "Game/Prefabs/GamePrefabs.h"
#include "CameraController.h"

#include <memory>

namespace WizardRaid
{
	void TitleScene::OnInit()
	{
	}

	void TitleScene::OnStart()
	{
		auto camera = std::make_unique<GameObject>();
		camera->SetName(L"MainCamera");
		camera->GetTransform().position = Vector2(640.0f, 360.0f);
		camera->AddComponent<Camera>();
		camera->AddComponent<CameraController>();

		auto ufo = GamePrefabs::CreateUFO();

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
		
		camera->GetComponent<CameraController>()->SetTargetObject(*ufo);

		AddObject(std::move(camera));
		AddObject(std::move(ufo));
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
