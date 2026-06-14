#include "TitleScene.h"

#include "SpriteRenderer.h"
#include "SpriteRig.h"

#include "Camera.h"
#include "Game/Prefabs/GamePrefabs.h"
#include "CameraController.h"

#include "Game/Characters/CoffiaCharacterFactory.h"
#include "Animation.h"
#include "PlayerCtrl.h"
#include "CoffiaAniCtrl.h"
#include "UFOStats.h"
#include "Canvas.h"
#include "UIText.h"
#include "UITransform.h"

#include <cwchar>
#include <memory>

namespace WizardRaid
{
	namespace
	{
		class UFOEnergyText : public Component
		{
		public:
			void SetStats(UFOStats* stats) { m_stats = stats; }

			void Start() override
			{
				m_text = GetOwner()->GetComponent<UIText>();
				UpdateText();
			}

			void Update(float deltaTime) override
			{
				(void)deltaTime;
				UpdateText();
			}

		private:
			void UpdateText()
			{
				if (!m_stats || !m_text)
				{
					return;
				}

				wchar_t buffer[64] = {};
				swprintf_s(
					buffer,
					L"Energy %.0f / %.0f",
					m_stats->GetEnergy(),
					m_stats->GetMaxEnergy());

				m_text->SetText(buffer);
			}

			UFOStats* m_stats = nullptr;
			UIText* m_text = nullptr;
		};
	}

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

		auto table = std::make_unique<GameObject>();
		table->SetName(L"Table");
		table->GetTransform().position = Vector2(640.0f, 520.0f);
		table->AddComponent<SpriteRenderer>(L"tTable");
		table->GetComponent<SpriteRenderer>()->SetRenderOrder(200);

		auto background = std::make_unique<GameObject>();
		background->SetName(L"Background");
		background->GetTransform().position = Vector2(640.0f, 360.0f);
		background->AddComponent<SpriteRenderer>(L"tBackgorund_Shop");
		background->GetComponent<SpriteRenderer>()->SetRenderOrder(-1000);

		auto coffia = std::make_unique<GameObject>();
		coffia->SetName(L"Coffia");
		coffia->GetTransform().position = Vector2(640.0f, 320.0f);
		coffia->GetTransform().scale = Vector2(0.55f, 0.55f);
		//coffia->AddComponent<PlayerCtrl>();
		coffia->AddComponent<CoffiaAniCtrl>();

		SpriteRig* rig = coffia->AddComponent<SpriteRig>();
		CoffiaCharacterFactory::ConfigureRig(*rig);
		Animator* animator = coffia->AddComponent<Animator>();
		CoffiaCharacterFactory::ConfigureAnimator(*animator);

		auto ufo = GamePrefabs::CreateUFO();
		UFOStats* ufoStats = ufo->GetComponent<UFOStats>();

		camera->GetComponent<CameraController>()->SetTargetObject(*ufo);

		auto hud = std::make_unique<GameObject>();
		hud->SetName(L"HUD");
		hud->AddComponent<Canvas>();

		auto energyText = std::make_unique<GameObject>();
		energyText->SetName(L"UFOEnergyText");

		UITransform* energyTextTransform = energyText->AddComponent<UITransform>();
		energyTextTransform->SetAnchorMin(Vector2(0.0f, 0.0f));
		energyTextTransform->SetAnchorMax(Vector2(0.0f, 0.0f));
		energyTextTransform->SetPivot(Vector2(0.0f, 0.0f));
		energyTextTransform->SetAnchoredPosition(Vector2(24.0f, 20.0f));
		energyTextTransform->SetSize(Vector2(260.0f, 36.0f));

		UIText* energyTextRenderer = energyText->AddComponent<UIText>();
		energyTextRenderer->SetFontSize(24.0f);
		energyTextRenderer->SetColor(D2D1::ColorF(0.96f, 0.98f, 1.0f, 1.0f));
		energyTextRenderer->SetRenderOrder(10);

		UFOEnergyText* energyTextBinder = energyText->AddComponent<UFOEnergyText>();
		energyTextBinder->SetStats(ufoStats);

		hud->AddChild(std::move(energyText));

		AddObject(std::move(camera));
		AddObject(std::move(ufo));
		AddObject(std::move(coffia));
		AddObject(std::move(background));
		AddObject(std::move(table));
		AddObject(std::move(hud));

		/*
		auto gear = std::make_unique<GameObject>();
		gear->AddComponent<SpriteRenderer>(L"tGear");
		gear->AddComponent<PlayerCtrl>();
		gear->GetTransform().scale = Vector2(0.2f, 0.2f);
		AddObject(std::move(gear));
		*/
	}
}
