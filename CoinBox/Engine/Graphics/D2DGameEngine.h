#pragma once

#include <d2d1_1.h>
#include <d3d11_1.h>
#include <dwrite.h>
#include <wrl/client.h>

#include "SceneManager.h"

// D2DGameEngine은 현재 프로젝트의 "엔진 본체" 역할을 합니다.
//
// 책임:
// - Direct2D / Direct3D 장치를 만든다.
// - 매 프레임 Tick -> Update -> Render 흐름을 실행한다.
// - 현재 실행 중인 SceneManager를 돌린다.
//
// 주의:
// - 실제 게임 오브젝트나 플레이어 로직은 엔진 밖의 Game 또는 Demo 폴더 쪽에 둡니다.
class D2DGameEngine
{
public:
    // hwnd는 Win32가 만든 창의 핸들입니다.
    // 엔진은 이 창에 Direct2D 화면을 붙입니다.
    HRESULT Initialize(HWND hwnd);

    // 프로그램 종료 시 D2D/D3D 리소스를 정리합니다.
    void Shutdown();

    // 게임 루프에서 매 프레임 한 번 호출됩니다.
    // 내부에서 시간 계산, 입력 갱신, Update, Render를 처리합니다.
    void Tick();

    // 창 크기가 바뀌었을 때 호출됩니다.
    // Direct2D가 그릴 대상 bitmap도 새 크기에 맞게 다시 만듭니다.
    void Resize(UINT width, UINT height);

private:
    // 장치와 무관한 리소스입니다.
    // 예: D2D Factory, DirectWrite Factory, 텍스트 포맷.
    HRESULT CreateDeviceIndependentResources();

    // 그래픽 장치와 관련된 리소스입니다.
    // 예: D3D Device, D2D Device, SwapChain.
    HRESULT CreateDeviceResources();

    // 창 크기에 의존하는 리소스입니다.
    // 예: 화면에 직접 그릴 D2D target bitmap.
    HRESULT CreateWindowSizeDependentResources();

    // 창 크기가 바뀌거나 장치를 다시 만들 때 기존 target bitmap 등을 버립니다.
    void DiscardWindowSizeDependentResources();

    // D2D/D3D 장치 전체를 버립니다.
    void DiscardDeviceResources();

    // 시작 시 사용할 씬들을 생성하고 SceneManager에 등록합니다.
    void InitializeScenes();

    // 게임 상태 갱신입니다. 실제 오브젝트 Update는 SceneManager가 처리합니다.
    void Update(float deltaTime);

    // 화면 그리기입니다. 실제 오브젝트 Render는 SceneManager가 처리합니다.
    void Render();

    // Win32 창 핸들입니다. Direct2D 출력 대상을 만들 때 필요합니다.
    HWND m_hwnd = nullptr;

    // 현재 창의 클라이언트 영역 크기입니다.
    // 클라이언트 영역은 제목 표시줄/테두리를 제외한 실제 그릴 수 있는 영역입니다.
    UINT m_width = 1;
    UINT m_height = 1;

    // ComPtr은 COM 객체를 자동으로 Release해주는 스마트 포인터입니다.
    // Direct2D/Direct3D 객체는 대부분 COM 객체라서 raw pointer보다 ComPtr이 안전합니다.
    Microsoft::WRL::ComPtr<ID2D1Factory1> m_d2dFactory;
    Microsoft::WRL::ComPtr<ID2D1Device> m_d2dDevice;
    Microsoft::WRL::ComPtr<ID2D1DeviceContext> m_d2dContext;
    Microsoft::WRL::ComPtr<ID2D1Bitmap1> m_d2dTargetBitmap;

    Microsoft::WRL::ComPtr<ID3D11Device> m_d3dDevice;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_d3dContext;
    Microsoft::WRL::ComPtr<IDXGISwapChain1> m_swapChain;

    Microsoft::WRL::ComPtr<IDWriteFactory> m_dwriteFactory;
    Microsoft::WRL::ComPtr<IDWriteTextFormat> m_textFormat;
    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> m_textBrush;

    // QueryPerformanceCounter용 타이머 값입니다.
    // deltaTime을 계산해서 프레임 속도와 무관하게 움직이기 위해 사용합니다.
    LARGE_INTEGER m_timerFrequency = {};
    LARGE_INTEGER m_lastFrameTime = {};
    bool m_comInitialized = false;

    // 백그라운드 씬과 현재 포그라운드 씬을 관리합니다.
    SceneManager m_sceneManager;
};
