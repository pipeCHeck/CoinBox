#include "Input.h"

// static 멤버 변수는 클래스 안에 선언만 하고,
// 실제 저장 공간은 .cpp 파일에서 한 번 정의해야 합니다.
HWND Input::m_hwnd = nullptr;
bool Input::m_currentKeys[256] = {};
bool Input::m_previousKeys[256] = {};
MousePosition Input::m_mousePosition = {};

void Input::Initialize(HWND hwnd)
{
    // 마우스 화면 좌표를 창 내부 좌표로 바꾸기 위해 창 핸들을 저장합니다.
    m_hwnd = hwnd;
}

void Input::Update()
{
    // Windows 가상 키 코드는 0~255 범위에 들어갑니다.
    // 예: VK_LEFT, VK_SPACE, 'A'
    for (int key = 0; key < 256; ++key)
    {
        // 이전 프레임 상태를 먼저 저장합니다.
        // 그래야 "이번 프레임에 막 눌렸는지/막 떼졌는지" 알 수 있습니다.
        m_previousKeys[key] = m_currentKeys[key];

        // GetAsyncKeyState는 현재 키가 눌려 있는지 알려주는 Win32 함수입니다.
        // 0x8000 비트가 켜져 있으면 현재 눌린 상태입니다.
        m_currentKeys[key] = (GetAsyncKeyState(key) & 0x8000) != 0;
    }

    // POINT는 Win32에서 x, y 좌표를 담는 구조체입니다.
    POINT point = {};

    // GetCursorPos는 화면 전체 기준 마우스 좌표를 가져옵니다.
    if (GetCursorPos(&point))
    {
        if (m_hwnd)
        {
            // 화면 전체 기준 좌표를 현재 창 내부 기준 좌표로 바꿉니다.
            ScreenToClient(m_hwnd, &point);
        }

        m_mousePosition.x = static_cast<float>(point.x);
        m_mousePosition.y = static_cast<float>(point.y);
    }
}

bool Input::IsKey(int key)
{
    // 키를 누르고 있는 동안 true입니다.
    return IsValidKey(key) && m_currentKeys[key];
}

bool Input::IsKeyDown(int key)
{
    // 현재는 눌려 있고, 이전 프레임에는 안 눌려 있었으면 첫 프레임 입력입니다.
    return IsValidKey(key) && m_currentKeys[key] && !m_previousKeys[key];
}

bool Input::IsKeyUp(int key)
{
    // 현재는 안 눌려 있고, 이전 프레임에는 눌려 있었으면 뗀 첫 프레임입니다.
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

MousePosition Input::GetMousePosition()
{
    return m_mousePosition;
}

int Input::ToVirtualKey(MouseButton button)
{
    // 우리가 만든 MouseButton 값을 Windows 가상 키 코드로 바꿉니다.
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
    // 배열 크기가 256이므로 범위 밖 인덱스 접근을 막습니다.
    return key >= 0 && key < 256;
}
