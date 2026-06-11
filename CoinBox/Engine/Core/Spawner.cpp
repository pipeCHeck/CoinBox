#include "Spawner.h"

#include "GameObject.h"

#include <cmath>

namespace
{
    constexpr float Pi = 3.1415926535f;
}

Spawner::Spawner()
    : m_rng(std::random_device{}())
{
}

Spawner::Spawner(const Prefab& prefab)
    : Spawner()
{
    m_prefab = prefab;
}

void Spawner::Start()
{
    if (m_started)
    {
        return;
    }

    m_started = true;
    m_elapsed = 0.0f;

    if (m_spawnOnStart)
    {
        Spawn();
    }
}

void Spawner::Update(float deltaTime)
{
    if (m_interval <= 0.0f || !CanSpawn())
    {
        return;
    }

    m_elapsed += deltaTime;
    if (m_elapsed < m_spawnDelay)
    {
        return;
    }

    const float activeElapsed = m_elapsed - m_spawnDelay;
    if (activeElapsed < m_interval)
    {
        return;
    }

    m_elapsed = m_spawnDelay;
    Spawn();
}

GameObject* Spawner::Spawn()
{
    if (!CanSpawn())
    {
        return nullptr;
    }

    GameObject* owner = GetOwner();
    if (!owner)
    {
        return nullptr;
    }

    std::unique_ptr<GameObject> instance = m_prefab.Instantiate();
    if (!instance)
    {
        return nullptr;
    }

    instance->GetTransform().position = instance->GetTransform().position + GetSpawnOffset();
    GameObject* spawned = owner->AddChild(std::move(instance));
    ++m_spawnedCount;

    if (m_onSpawn)
    {
        m_onSpawn(spawned);
    }

    return spawned;
}

bool Spawner::CanSpawn() const
{
    return m_prefab.IsValid()
        && (m_maxSpawnCount < 0 || m_spawnedCount < m_maxSpawnCount);
}

Vector2 Spawner::GetSpawnOffset()
{
    if (m_randomRadius <= 0.0f)
    {
        return m_localOffset;
    }

    std::uniform_real_distribution<float> angleDistribution(0.0f, Pi * 2.0f);
    std::uniform_real_distribution<float> radiusDistribution(0.0f, m_randomRadius);
    const float angle = angleDistribution(m_rng);
    const float radius = radiusDistribution(m_rng);

    return m_localOffset + Vector2(std::cos(angle) * radius, std::sin(angle) * radius);
}
