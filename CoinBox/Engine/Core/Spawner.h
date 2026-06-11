#pragma once

#include "Component.h"
#include "Prefab.h"

#include <functional>
#include <memory>
#include <random>

class Spawner : public Component
{
public:
    using SpawnCallback = std::function<void(GameObject*)>;

    Spawner();
    explicit Spawner(const Prefab& prefab);

    void Start() override;
    void Update(float deltaTime) override;

    void SetPrefab(const Prefab& prefab) { m_prefab = prefab; }
    const Prefab& GetPrefab() const { return m_prefab; }

    void SetInterval(float interval) { m_interval = interval; }
    float GetInterval() const { return m_interval; }

    void SetSpawnDelay(float delay) { m_spawnDelay = delay; }
    float GetSpawnDelay() const { return m_spawnDelay; }

    void SetSpawnOnStart(bool spawnOnStart) { m_spawnOnStart = spawnOnStart; }
    bool GetSpawnOnStart() const { return m_spawnOnStart; }

    void SetMaxSpawnCount(int maxSpawnCount) { m_maxSpawnCount = maxSpawnCount; }
    int GetMaxSpawnCount() const { return m_maxSpawnCount; }
    int GetSpawnedCount() const { return m_spawnedCount; }

    void SetLocalOffset(const Vector2& localOffset) { m_localOffset = localOffset; }
    const Vector2& GetLocalOffset() const { return m_localOffset; }

    void SetRandomRadius(float randomRadius) { m_randomRadius = randomRadius; }
    float GetRandomRadius() const { return m_randomRadius; }

    void SetOnSpawn(SpawnCallback callback) { m_onSpawn = callback; }

    GameObject* Spawn();
    bool CanSpawn() const;

private:
    Vector2 GetSpawnOffset();

    Prefab m_prefab;
    SpawnCallback m_onSpawn;
    std::mt19937 m_rng;
    float m_interval = 0.0f;
    float m_spawnDelay = 0.0f;
    float m_elapsed = 0.0f;
    float m_randomRadius = 0.0f;
    int m_maxSpawnCount = -1;
    int m_spawnedCount = 0;
    bool m_spawnOnStart = false;
    bool m_started = false;
    Vector2 m_localOffset = Vector2(0.0f, 0.0f);
};
