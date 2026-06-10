#include "framework.h"
#include "D2DGameEngine.h"
#include "Input.h"
#include "ResourceManager.h"
#include "Screen.h"


#include "Demo/DemoScenes.h"

#include "BackScene.h"
#include "TitleScene.h"

#include <algorithm>
#include <dxgi1_2.h>
#include <memory>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dwrite.lib")

using Microsoft::WRL::ComPtr;

namespace
{
    template <typename T>
    void SafeReleaseTarget(T& target)
    {
        target.Reset();
    }
}

HRESULT D2DGameEngine::Initialize(HWND hwnd)
{
    m_hwnd = hwnd;
    const HRESULT comHr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    m_comInitialized = SUCCEEDED(comHr);

    RECT clientRect = {};
    GetClientRect(m_hwnd, &clientRect);
    m_width = clientRect.right > clientRect.left
        ? static_cast<UINT>(clientRect.right - clientRect.left)
        : 1;
    m_height = clientRect.bottom > clientRect.top
        ? static_cast<UINT>(clientRect.bottom - clientRect.top)
        : 1;
    Screen::SetSize(m_width, m_height);
    Input::Initialize(m_hwnd);

    HRESULT hr = CreateDeviceIndependentResources();
    if (SUCCEEDED(hr))
    {
        hr = CreateDeviceResources();
    }

    QueryPerformanceFrequency(&m_timerFrequency);
    QueryPerformanceCounter(&m_lastFrameTime);

    if (SUCCEEDED(hr))
    {
        InitializeScenes();
    }

    return hr;
}

void D2DGameEngine::Shutdown()
{
    m_sceneManager.Clear();
    ResourceManager::Shutdown();
    DiscardDeviceResources();
    m_textFormat.Reset();
    m_dwriteFactory.Reset();
    m_d2dFactory.Reset();

    if (m_comInitialized)
    {
        CoUninitialize();
        m_comInitialized = false;
    }
}

void D2DGameEngine::Tick()
{
    LARGE_INTEGER now = {};         // int 랑 비교 못하는 엄청 큰 정수형 winAPI 자료형
    QueryPerformanceCounter(&now);  // 현재 시간값 (고성능 / 엄청 큰 값이 나올 수 있음)

    float deltaTime =
        static_cast<float>(now.QuadPart - m_lastFrameTime.QuadPart) /
        static_cast<float>(m_timerFrequency.QuadPart);  // 이전 
    m_lastFrameTime = now;  // 다음 프레임 연산에 사용될 예정

    if (deltaTime > 0.2f)
        deltaTime = 0.2f;   // 컴퓨터가 너무 오래 끊기면 순간이동하는 정도가 너무 심해지니 적당히 조정하기

    Input::Update();        // 입력 먼저 받고
    Update(deltaTime);      // 업데이트 돌리고
    Render();               // 렌더 호출
}

void D2DGameEngine::Resize(UINT width, UINT height)
{
    width = width > 0 ? width : 1;
    height = height > 0 ? height : 1;

    if (width == m_width && height == m_height)
    {
        return;
    }

    m_width = width;
    m_height = height;
    Screen::SetSize(m_width, m_height);

    if (!m_swapChain)
    {
        return;
    }

    if (m_d2dContext)
    {
        m_d2dContext->SetTarget(nullptr);
    }

    DiscardWindowSizeDependentResources();

    HRESULT hr = m_swapChain->ResizeBuffers(
        0,
        m_width,
        m_height,
        DXGI_FORMAT_UNKNOWN,
        0);

    if (SUCCEEDED(hr))
    {
        hr = CreateWindowSizeDependentResources();
    }

    if (FAILED(hr))
    {
        DiscardDeviceResources();
        CreateDeviceResources();
    }
}

HRESULT D2DGameEngine::CreateDeviceIndependentResources()
{
    D2D1_FACTORY_OPTIONS factoryOptions = {};

#if defined(_DEBUG)
    factoryOptions.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
#endif

    HRESULT hr = D2D1CreateFactory(
        D2D1_FACTORY_TYPE_SINGLE_THREADED,
        __uuidof(ID2D1Factory1),
        &factoryOptions,
        reinterpret_cast<void**>(m_d2dFactory.GetAddressOf()));

    if (SUCCEEDED(hr))
    {
        hr = DWriteCreateFactory(
            DWRITE_FACTORY_TYPE_SHARED,
            __uuidof(IDWriteFactory),
            reinterpret_cast<IUnknown**>(m_dwriteFactory.GetAddressOf()));
    }

    if (SUCCEEDED(hr))
    {
        hr = m_dwriteFactory->CreateTextFormat(
            L"Segoe UI",
            nullptr,
            DWRITE_FONT_WEIGHT_SEMI_BOLD,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            22.0f,
            L"ko-kr",
            &m_textFormat);
    }

    return hr;
}

HRESULT D2DGameEngine::CreateDeviceResources()
{
    UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#if defined(_DEBUG)
    creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    const D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };

    D3D_FEATURE_LEVEL createdFeatureLevel = D3D_FEATURE_LEVEL_10_0;
    HRESULT hr = D3D11CreateDevice(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        creationFlags,
        featureLevels,
        ARRAYSIZE(featureLevels),
        D3D11_SDK_VERSION,
        &m_d3dDevice,
        &createdFeatureLevel,
        &m_d3dContext);

    if (FAILED(hr))
    {
        hr = D3D11CreateDevice(
            nullptr,
            D3D_DRIVER_TYPE_WARP,
            nullptr,
            creationFlags,
            featureLevels,
            ARRAYSIZE(featureLevels),
            D3D11_SDK_VERSION,
            &m_d3dDevice,
            &createdFeatureLevel,
            &m_d3dContext);
    }

    ComPtr<IDXGIDevice> dxgiDevice;
    if (SUCCEEDED(hr))
    {
        hr = m_d3dDevice.As(&dxgiDevice);
    }

    if (SUCCEEDED(hr))
    {
        hr = m_d2dFactory->CreateDevice(dxgiDevice.Get(), &m_d2dDevice);
    }

    if (SUCCEEDED(hr))
    {
        hr = m_d2dDevice->CreateDeviceContext(
            D2D1_DEVICE_CONTEXT_OPTIONS_NONE,
            &m_d2dContext);
    }

    ComPtr<IDXGIAdapter> dxgiAdapter;
    if (SUCCEEDED(hr))
    {
        hr = dxgiDevice->GetAdapter(&dxgiAdapter);
    }

    ComPtr<IDXGIFactory2> dxgiFactory;
    if (SUCCEEDED(hr))
    {
        hr = dxgiAdapter->GetParent(
            __uuidof(IDXGIFactory2),
            reinterpret_cast<void**>(dxgiFactory.GetAddressOf()));
    }

    if (SUCCEEDED(hr))
    {
        DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
        swapChainDesc.Width = m_width;
        swapChainDesc.Height = m_height;
        swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        swapChainDesc.SampleDesc.Count = 1;
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.BufferCount = 2;
        swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;

        hr = dxgiFactory->CreateSwapChainForHwnd(
            m_d3dDevice.Get(),
            m_hwnd,
            &swapChainDesc,
            nullptr,
            nullptr,
            &m_swapChain);
    }

    if (SUCCEEDED(hr))
    {
        dxgiFactory->MakeWindowAssociation(m_hwnd, DXGI_MWA_NO_ALT_ENTER);
        hr = CreateWindowSizeDependentResources();
    }

    return hr;
}

HRESULT D2DGameEngine::CreateWindowSizeDependentResources()
{
    ComPtr<IDXGISurface> backBuffer;
    HRESULT hr = m_swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));

    if (SUCCEEDED(hr))
    {
        const D2D1_BITMAP_PROPERTIES1 bitmapProperties = D2D1::BitmapProperties1(
            D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
            D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE));

        hr = m_d2dContext->CreateBitmapFromDxgiSurface(
            backBuffer.Get(),
            &bitmapProperties,
            &m_d2dTargetBitmap);
    }

    if (SUCCEEDED(hr))
    {
        m_d2dContext->SetTarget(m_d2dTargetBitmap.Get());
        m_d2dContext->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);

        ResourceManager::Initialize(m_d2dContext.Get());
        ResourceManager::SetAssetRoot(L"Assets");

        hr = m_d2dContext->CreateSolidColorBrush(
            D2D1::ColorF(0.93f, 0.95f, 0.98f),
            &m_textBrush);
    }

    return hr;
}

void D2DGameEngine::DiscardWindowSizeDependentResources()
{
    ResourceManager::ClearTextures();
    SafeReleaseTarget(m_textBrush);
    SafeReleaseTarget(m_d2dTargetBitmap);
}

void D2DGameEngine::DiscardDeviceResources()
{
    if (m_d2dContext)
    {
        m_d2dContext->SetTarget(nullptr);
    }

    DiscardWindowSizeDependentResources();
    m_swapChain.Reset();
    m_d2dContext.Reset();
    m_d2dDevice.Reset();
    m_d3dContext.Reset();
    m_d3dDevice.Reset();
}

void D2DGameEngine::InitializeScenes()
{
    // 엔진 시작 시 씬들을 등록하고, 현재 사용할 포그라운드 씬을 선택합니다.
    //m_sceneManager.SetBackgroundScene(std::make_unique<DemoGame::DemoBackgroundScene>());
    //m_sceneManager.AddForegroundScene(L"Demo", std::make_unique<DemoGame::DemoScene>());
    m_sceneManager.SetBackgroundScene(std::make_unique<WizardRaid::BackScene>());
    m_sceneManager.AddForegroundScene(L"Demo", std::make_unique<WizardRaid::TitleScene>());
    m_sceneManager.SetCurrentScene(L"Demo");
}

void D2DGameEngine::Update(float deltaTime)
{
    // 백그라운드 씬은 계속 돌고, 포그라운드 씬은 현재 선택된 하나만 돕니다.
    m_sceneManager.UpdateBackground(deltaTime);
    m_sceneManager.UpdateCurrent(deltaTime);
}

void D2DGameEngine::Render()
{
    if (!m_d2dContext || !m_swapChain)
    {
        return;
    }

    m_d2dContext->BeginDraw();
    m_d2dContext->Clear(D2D1::ColorF(0.07f, 0.09f, 0.12f));

    // 실제 게임 화면은 현재 포그라운드 씬이 그립니다.
    m_sceneManager.RenderCurrent(m_d2dContext.Get());

    /*
    const float width = static_cast<float>(m_width);
    const D2D1_RECT_F textRect = D2D1::RectF(24.0f, 22.0f, width - 24.0f, 80.0f);
    m_d2dContext->DrawTextW(
        L"CoinBox D2D 1.1 starter - Left/Right arrows move the circle",
        61,
        m_textFormat.Get(),
        textRect,
        m_textBrush.Get());
    */

    HRESULT hr = m_d2dContext->EndDraw();
    if (hr == D2DERR_RECREATE_TARGET)
    {
        DiscardDeviceResources();
        CreateDeviceResources();
        return;
    }

    m_swapChain->Present(1, 0);
}



