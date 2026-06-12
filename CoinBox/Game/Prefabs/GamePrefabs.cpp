#include "Game/Prefabs/GamePrefabs.h"

#include "Game/Objects/UFOProjectile.h"
#include "CircleCollider2D.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "UFOAttack.h"
#include "UFOController.h"
#include "UFODash.h"
#include "UFOMovement.h"
#include "UFOStats.h"
#include "UFOSuction.h"

#include <memory>

namespace WizardRaid
{
    std::unique_ptr<GameObject> GamePrefabs::CreateUFO()
    {
        auto ufo = std::make_unique<GameObject>();
        ufo->SetName(L"UFO");
        ufo->GetTransform().position = Vector2(640.0f, 520.0f);
        ufo->GetTransform().scale = Vector2(0.45f, 0.45f);

        auto renderer = ufo->AddComponent<SpriteRenderer>(L"tUFO_test");
        renderer->SetRenderOrder(100);

        auto collider = ufo->AddComponent<CircleCollider2D>(80.0f);
        collider->SetTrigger(false);

        ufo->AddComponent<UFOStats>();
        ufo->AddComponent<UFOMovement>();
        ufo->AddComponent<UFODash>();

        UFOAttack* attack = ufo->AddComponent<UFOAttack>();
        attack->SetProjectilePrefab(CreateUFOProjectilePrefab());

        ufo->AddComponent<UFOSuction>();
        ufo->AddComponent<UFOController>();

        return ufo;
    }

    Prefab GamePrefabs::CreateUFOProjectilePrefab()
    {
        return Prefab([]()
            {
                auto projectile = std::make_unique<GameObject>();
                projectile->SetName(L"UFOProjectile");
                projectile->GetTransform().scale = Vector2(0.25f, 0.25f);

                auto renderer = projectile->AddComponent<SpriteRenderer>(L"tUFO_Projectile_test");
                renderer->SetRenderOrder(300);

                auto projectileMove = projectile->AddComponent<UFOProjectile>();
                projectileMove->SetSpeed(1000.0f);
                projectileMove->SetLifeTime(5.0f);
                projectileMove->SetDamage(10.0f);

                return projectile;
            });
    }

    Prefab GamePrefabs::CreatePlayerBulletPrefab()
    {
        return CreateUFOProjectilePrefab();
    }
}
