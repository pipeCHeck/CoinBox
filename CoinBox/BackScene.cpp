#include "BackScene.h"

#include "Game/Characters/CoffiaCharacterFactory.h"

namespace WizardRaid
{
	void BackScene::OnInit() 
	{
		ResourceManager::LoadTexture(L"tGear", L"Images/Gear.png");
		ResourceManager::LoadTexture(L"tBackgorund_Shop", L"Images/CoffiaDailyShop/Backgorund_Shop.png");
		ResourceManager::LoadTexture(L"tTable", L"Images/CoffiaDailyShop/Table.png");
		CoffiaCharacterFactory::LoadResources();
	}

}
