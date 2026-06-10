#pragma once

#include <Windows.h>
#include "Vector2.h"

enum class MouseButton
{
    Left,
    Right,
    Middle,
    X1,
    X2
};

// 게임 전체에서 공유하는 입력 상태입니다.
// D2DGameEngine::Tick 시작 부분에서 Update를 한 번 호출한 뒤 사용합니다.
class Input
{
public:
    static void Initialize(HWND hwnd);
    static void Update();

    // 키를 누르고 있는 동안 true입니다.
    static bool IsKey(int key);

    // 키를 누른 첫 프레임에만 true입니다.
    static bool IsKeyDown(int key);

    // 키를 뗀 첫 프레임에만 true입니다.
    static bool IsKeyUp(int key);

    // 마우스 버튼을 누르고 있는 동안 true입니다.
    static bool IsMouse(MouseButton button);

    // 마우스 버튼을 누른 첫 프레임에만 true입니다.
    static bool IsMouseDown(MouseButton button);

    // 마우스 버튼을 뗀 첫 프레임에만 true입니다.
    static bool IsMouseUp(MouseButton button);

    static Vector2 GetMousePosition();
    static Vector2 GetMousePositionInScreen();
    static Vector2 GetMousePositionInScreenCenter();
    static Vector2 GetMousePositionNormalized();

private:
    static int ToVirtualKey(MouseButton button);
    static bool IsValidKey(int key);

    static HWND m_hwnd;
    static bool m_currentKeys[256];
    static bool m_previousKeys[256];
    static Vector2 m_mousePosition;
};
