#pragma once

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

    Vector2& operator+=(const Vector2& other) 
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2 operator-(const Vector2& other) const
    {
        return Vector2(x - other.x, y - other.y);
    }

    Vector2& operator-=(const Vector2& other) 
    {
        x -= other.x;
        y -= other.y;
        return *this;
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

    float Length() const
    {
        return std::sqrt(x * x + y * y);
    }

    Vector2& Normalize()
    {
        float length = Length();

        if (length <= 0.0001f)
        {
            x = 0.0f;
            y = 0.0f;
            return *this;
        }

        x /= length;
        y /= length;
        return *this;
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
