#pragma once

#include "Component.h"
#include "Vector2.h"

// 모든 GameObject가 기본으로 가지는 위치/회전/크기 Component입니다.
// rotation은 D2D에서 쓰기 편하게 degree 단위로 둡니다.
class Transform : public Component
{
public:
    Vector2 position = Vector2(0.0f, 0.0f);
    float rotation = 0.0f;
    Vector2 scale = Vector2(1.0f, 1.0f);

    Transform operator+(const Transform& other) const
    {
        Transform result;
        result.position = position + other.position;
        result.rotation = rotation + other.rotation;
        result.scale = scale * other.scale;
        return result;
    }
};
