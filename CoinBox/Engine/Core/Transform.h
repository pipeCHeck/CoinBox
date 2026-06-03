#pragma once

#include "Component.h"

// 2D 좌표나 크기를 표현하는 단순한 값 타입입니다.
struct Vector2
{
    float x = 0.0f;
    float y = 0.0f;

    Vector2() = default;
    Vector2(float xValue, float yValue)
        : x(xValue), y(yValue) { }
};

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
        result.position.x = position.x + other.position.x;
        result.position.y = position.y + other.position.y;
        result.rotation = rotation + other.rotation;
        result.scale.x = scale.x * other.scale.x;
        result.scale.y = scale.y * other.scale.y;
        return result;
    }
};
