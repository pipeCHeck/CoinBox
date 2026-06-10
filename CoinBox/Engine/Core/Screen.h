#pragma once

#include "Vector2.h"

class Screen
{
public:
    static void SetSize(unsigned int width, unsigned int height);

    static float GetWidth() { return m_width; }
    static float GetHeight() { return m_height; }
    static Vector2 GetSize() { return Vector2(m_width, m_height); }
    static Vector2 GetCenter() { return Vector2(m_width * 0.5f, m_height * 0.5f); }

private:
    static float m_width;
    static float m_height;
};
