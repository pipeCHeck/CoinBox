#pragma once

#include "Component.h"

#include <cmath>

// 2D 좌표나 크기를 표현하는 단순한 값 타입입니다.
struct Vector2
{
    float x = 0.0f;
    float y = 0.0f;

    Vector2() = default;
    Vector2(float xValue, float yValue)
        : x(xValue), y(yValue) { }

    Vector2 operator+(const Vector2& other) const
    {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 operator-(const Vector2& other) const
    {
        return Vector2(x - other.x, y - other.y);
    }

    Vector2 operator*(const Vector2& other) const
    {
        return Vector2(x * other.x, y * other.y);
    }

    Vector2 operator*(float value) const
    {
        return Vector2(x * value, y * value);
    }

    Vector2 operator/(float value) const
    {
        return Vector2(x / value, y / value);
    }
};

inline Vector2 operator*(float value, const Vector2& vector)
{
    return vector * value;
}

inline Vector2 RotateVector(const Vector2& value, float degrees)
{
    constexpr float pi = 3.1415926535f;
    const float radians = degrees * pi / 180.0f;
    const float cosA = std::cos(radians);
    const float sinA = std::sin(radians);

    return Vector2(
        value.x * cosA - value.y * sinA,
        value.x * sinA + value.y * cosA);
}

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
