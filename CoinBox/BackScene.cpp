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

		ResourceManager::LoadTexture(L"tUFO_test", L"Images/UFO_test.png");
		ResourceManager::LoadTexture(L"tUFO_Projectile_test", L"Images/UFO_Projectile_test.png");
	}

}
