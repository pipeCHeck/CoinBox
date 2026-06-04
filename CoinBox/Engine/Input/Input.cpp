#include "Input.h"
#include "framework.h"

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
    for (int key = 0; key < 256; key++)
    {
        m_previousKeys[key] = m_currentKeys[key];   // 이전 프레임의 입력 여부를 저장

        // GetAsyncKeyState는 현재 키가 눌려 있는지 알려주는 Win32 함수입니다.
        // 0x8000 비트가 켜져 있으면 현재 눌린 상태입니다.
        m_currentKeys[key] = (GetAsyncKeyState(key) & 0x8000) != 0; // and 연산자를 통해서 눌렸는지 여부 확인

        /*
        if (m_currentKeys[key])
        {
            wchar_t buffer[128];
            swprintf_s(buffer, L"Key down: %d\n", key);
            OutputDebugStringW(buffer);
        }*/
    }

    POINT point = {};
    if (GetCursorPos(&point))   // 전체화면 기준 마우스 좌표 가져옴
    {
        if (m_hwnd != nullptr)              // 핸들이 존재하면
            ScreenToClient(m_hwnd, &point); // 창 내부 기준 좌표로 변환

        m_mousePosition.x = static_cast<float>(point.x);    // 마우스 위치값 저장
        m_mousePosition.y = static_cast<float>(point.y);
    }
}

// 키를 누르고 있는가?
bool Input::IsKey(int key)
{
    return IsValidKey(key) && m_currentKeys[key];
}

// 키를 누른 순간만
bool Input::IsKeyDown(int key)
{
    return IsValidKey(key) && m_currentKeys[key] && !m_previousKeys[key];
}

// 키를 뗀 순간만
bool Input::IsKeyUp(int key)
{
    return IsValidKey(key) && !m_currentKeys[key] && m_previousKeys[key];
}

// 마우스 입력 여부
bool Input::IsMouse(MouseButton button)
{
    return IsKey(ToVirtualKey(button));
}

// 마우스 입력을 한 순간
bool Input::IsMouseDown(MouseButton button)
{
    return IsKeyDown(ToVirtualKey(button));
}

// 마우스 입력을 뗀 순간 
bool Input::IsMouseUp(MouseButton button)
{
    return IsKeyUp(ToVirtualKey(button));
}

// 마우스 위치값 반환
MousePosition Input::GetMousePosition()
{
    return m_mousePosition;
}

// enum 값을 실제 키값으로 변환
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

// 가능한 입력 가짓수 내인지 확인
bool Input::IsValidKey(int key)
{
    return key >= 0 && key < 256;
}
