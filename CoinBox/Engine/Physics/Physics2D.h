#pragma once

#include "Collision2D.h"

#include <set>
#include <vector>

class Collider2D;

class Physics2D
{
public:
    static void RegisterCollider(Collider2D* collider);
    static void UnregisterCollider(Collider2D* collider);
    static void Step(float deltaTime);
    static void Clear();

private:
    struct ColliderPair
    {
        Collider2D* first = nullptr;
        Collider2D* second = nullptr;

        bool operator<(const ColliderPair& other) const;
    };

    static ColliderPair MakePair(Collider2D* first, Collider2D* second);
    static bool ShouldCollide(Collider2D* first, Collider2D* second);
    static bool CheckCollision(Collider2D* first, Collider2D* second, Collision2D& collision);
    static Collision2D ReverseCollision(const Collision2D& collision);
    static void DispatchEnter(const Collision2D& firstCollision);
    static void DispatchStay(const Collision2D& firstCollision);
    static void DispatchExit(Collider2D* first, Collider2D* second);

    static std::vector<Collider2D*> s_colliders;
    static std::set<ColliderPair> s_collidingPairs;
};
