#pragma once

#include "Vector2.h"

class Collider2D;

struct Collision2D
{
    Collider2D* self = nullptr;
    Collider2D* other = nullptr;
    Vector2 point = Vector2(0.0f, 0.0f);
    Vector2 normal = Vector2(0.0f, 0.0f);
    float penetration = 0.0f;
    bool isTrigger = false;
};
