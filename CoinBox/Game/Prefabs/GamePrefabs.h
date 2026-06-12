#pragma once

#include "Prefab.h"

#include <memory>

class GameObject;

namespace WizardRaid
{
    class GamePrefabs
    {
    public:
        static std::unique_ptr<GameObject> CreateUFO();
        static Prefab CreateUFOProjectilePrefab();
        static Prefab CreatePlayerBulletPrefab();
    };
}
