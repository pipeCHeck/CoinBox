#include "BackScene.h"

#include "Game/Characters/CoffiaCharacterFactory.h"

namespace WizardRaid
{
	void BackScene::OnInit() 
	{
		ResourceManager::LoadTexture(L"tGear", L"Images/Gear.png");
		CoffiaCharacterFactory::LoadResources();
	}

}
