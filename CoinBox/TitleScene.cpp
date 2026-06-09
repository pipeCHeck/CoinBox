#include "TitleScene.h"
#include "SpriteRenderer.h"

namespace WizardRaid
{
	void TitleScene::OnStart()
	{
		auto grid = std::make_unique<GameObject>();
		grid->AddComponent<SpriteRenderer>(L"tGear");
		AddObject(std::move(grid));
	}
}