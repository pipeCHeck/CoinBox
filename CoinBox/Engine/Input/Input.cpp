#include "Input.h"

#include "framework.h"
#include "Screen.h"

namespace
{
    float ClampFloat(float value, float minValue, float maxValue)
    {
        if (value < minValue)
        {
            return minValue;
        }

        if (value > maxValue)
        {
            return maxValue;
        }

        return value;
    }
}

HWND Input::m_hwnd = nullptr;
bool Input::m_currentKeys[256] = {};
bool Input::m_previousKeys[256] = {};
Vector2 Input::m_mousePosition = {};

void Input::Initialize(HWND hwnd)
{
    m_hwnd = hwnd;
}

void Input::Update()
{
    for (int key = 0; key < 256; key++)
    {
        m_previousKeys[key] = m_currentKeys[key];
        m_currentKeys[key] = (GetAsyncKeyState(key) & 0x8000) != 0;
    }

    POINT point = {};
    if (GetCursorPos(&point))
    {
        if (m_hwnd != nullptr)
        {
            ScreenToClient(m_hwnd, &point);
        }

        m_mousePosition.x = static_cast<float>(point.x);
        m_mousePosition.y = static_cast<float>(point.y);
    }
}

bool Input::IsKey(int key)
{
    return IsValidKey(key) && m_currentKeys[key];
}

bool Input::IsKeyDown(int key)
{
    return IsValidKey(key) && m_currentKeys[key] && !m_previousKeys[key];
}

bool Input::IsKeyUp(int key)
{
    return IsValidKey(key) && !m_currentKeys[key] && m_previousKeys[key];
}

bool Input::IsMouse(MouseButton button)
{
    return IsKey(ToVirtualKey(button));
}

bool Input::IsMouseDown(MouseButton button)
{
    return IsKeyDown(ToVirtualKey(button));
}

bool Input::IsMouseUp(MouseButton button)
{
    return IsKeyUp(ToVirtualKey(button));
}

Vector2 Input::GetMousePosition()
{
    return m_mousePosition;
}

Vector2 Input::GetMousePositionInScreen()
{
    return Vector2(
        ClampFloat(m_mousePosition.x, 0.0f, Screen::GetWidth()),
        ClampFloat(m_mousePosition.y, 0.0f, Screen::GetHeight()));
}

Vector2 Input::GetMousePositionInScreenCenter()
{
    return GetMousePositionInScreen() - Screen::GetCenter();
}

Vector2 Input::GetMousePositionNormalized()
{
    const Vector2 position = GetMousePositionInScreen();
    return Vector2(
        position.x / Screen::GetWidth(),
        position.y / Screen::GetHeight());
}

int Input::ToVirtualKey(MouseButton button)
{
    switch (button)
    {
    case MouseButton::Left:
        return VK_LBUTTON;
    case MouseButton::Right:
        return VK_RBUTTON;
    case MouseButton::Middle:
        return VK_MBUTTON;
    case MouseButton::X1:
        return VK_XBUTTON1;
    case MouseButton::X2:
        return VK_XBUTTON2;
    default:
        return 0;
    }
}

bool Input::IsValidKey(int key)
{
    return key >= 0 && key < 256;
}
