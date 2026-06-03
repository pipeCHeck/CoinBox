// CoinBox.cpp
//
// 이 파일은 Win32 프로그램의 시작점입니다.
// 창을 만들고, Windows 메시지를 처리하고, 매 프레임 엔진의 Tick을 호출합니다.
// 실제 게임/엔진 로직은 D2DGameEngine 쪽에 있습니다.

#include "framework.h"
#include "CoinBox.h"
#include "D2DGameEngine.h"

// 리소스에서 읽어올 문자열의 최대 길이입니다.
#define MAX_LOADSTRING 100

// Win32에서 자주 쓰는 전역 상태입니다.
HINSTANCE hInst;                                // 현재 실행 중인 프로그램 인스턴스 핸들입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 창 제목 문자열입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // Windows에 등록할 창 클래스 이름입니다.

// 프로그램 전체에서 사용할 엔진 객체입니다.
// 메시지 루프에서 매 프레임 gGameEngine.Tick()을 호출합니다.
D2DGameEngine gGameEngine;

// 함수 원형 선언입니다.
// C++은 함수를 사용하기 전에 그 함수의 이름/매개변수/반환 타입을 알고 있어야 합니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// Windows GUI 프로그램의 시작 함수입니다.
// 콘솔 프로그램의 main()과 비슷한 역할을 합니다.
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    // 지금 사용하지 않는 매개변수라서 컴파일러 경고를 막습니다.
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // .rc 리소스 파일에 있는 문자열을 읽어옵니다.
    // IDS_APP_TITLE은 창 제목, IDC_COINBOX는 창 클래스 이름입니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_COINBOX, szWindowClass, MAX_LOADSTRING);

    // Windows에 "이런 종류의 창을 만들겠다"라고 등록합니다.
    MyRegisterClass(hInstance);

    // 실제 창을 만들고 엔진을 초기화합니다.
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    // 메뉴 단축키 처리를 위한 Windows 리소스입니다.
    // 게임 엔진 핵심 로직과는 크게 관련 없습니다.
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_COINBOX));

    // MSG는 Windows 메시지를 담는 구조체입니다.
    // 예: 창 닫기, 크기 변경, 메뉴 클릭 등.
    MSG msg = {};

    // 메인 루프입니다.
    //
    // 1. 쌓여 있는 Windows 메시지를 모두 처리합니다.
    // 2. 종료 메시지가 아니라면 엔진을 한 프레임 실행합니다.
    while (msg.message != WM_QUIT)
    {
        // PeekMessage는 메시지가 있으면 꺼내고, 없으면 바로 넘어갑니다.
        // GetMessage처럼 멈춰서 기다리지 않기 때문에 게임 루프에 적합합니다.
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            // 메뉴 단축키를 먼저 처리합니다.
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                // 키보드 메시지를 문자 메시지로 변환할 필요가 있을 때 변환합니다.
                TranslateMessage(&msg);

                // 메시지를 WndProc 함수로 보냅니다.
                DispatchMessage(&msg);
            }
        }

        // 실제 게임/엔진 한 프레임을 실행합니다.
        gGameEngine.Tick();
    }

    // 프로그램 종료 코드입니다.
    return (int)msg.wParam;
}

// Windows 창 클래스를 등록합니다.
// 창 클래스는 "앞으로 만들 창의 기본 설정 묶음"이라고 보면 됩니다.
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    // WNDCLASSEXW는 창 클래스 설정을 담는 구조체입니다.
    WNDCLASSEXW wcex;

    // Win32 API는 구조체 크기를 직접 알려줘야 하는 경우가 많습니다.
    wcex.cbSize = sizeof(WNDCLASSEX);

    // 창의 가로/세로 크기가 바뀌면 다시 그리도록 하는 스타일입니다.
    wcex.style          = CS_HREDRAW | CS_VREDRAW;

    // 이 창에서 발생하는 메시지를 처리할 함수입니다.
    wcex.lpfnWndProc    = WndProc;

    // 추가 메모리 공간입니다. 지금은 사용하지 않으므로 0입니다.
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;

    // 현재 프로그램 인스턴스입니다.
    wcex.hInstance      = hInstance;

    // 창 아이콘입니다.
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_COINBOX));

    // 마우스 커서입니다.
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);

    // 기본 배경 브러시입니다.
    // 우리는 Direct2D에서 직접 배경을 지우므로 nullptr로 둡니다.
    wcex.hbrBackground  = nullptr;

    // 메뉴 리소스입니다.
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_COINBOX);

    // 창 클래스 이름입니다.
    wcex.lpszClassName  = szWindowClass;

    // 작은 아이콘입니다.
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    // 설정한 창 클래스를 Windows에 등록합니다.
    return RegisterClassExW(&wcex);
}

// 실제 창을 만들고 D2DGameEngine을 초기화합니다.
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   // 인스턴스 핸들을 전역 변수에 저장합니다.
   hInst = hInstance;

   // CreateWindowW는 Unicode 버전의 Win32 창 생성 함수입니다.
   //
   // 인자 순서:
   // 1. 창 클래스 이름
   // 2. 창 제목
   // 3. 창 스타일
   // 4. x 위치
   // 5. y 위치
   // 6. 창 너비
   // 7. 창 높이
   // 8. 부모 창
   // 9. 메뉴
   // 10. 프로그램 인스턴스
   // 11. 추가 데이터
   HWND hWnd = CreateWindowW(
       szWindowClass,
       szTitle,
       WS_OVERLAPPEDWINDOW,
       CW_USEDEFAULT,
       CW_USEDEFAULT,
       1280,
       720,
       nullptr,
       nullptr,
       hInstance,
       nullptr);

   // 창 생성에 실패하면 hWnd는 nullptr입니다.
   if (!hWnd)
   {
      return FALSE;
   }

   // 만든 창 핸들을 엔진에 넘겨서 Direct2D 렌더링 준비를 합니다.
   if (FAILED(gGameEngine.Initialize(hWnd)))
   {
       MessageBoxW(hWnd, L"D2D 1.1 렌더러 초기화에 실패했습니다.", szTitle, MB_OK | MB_ICONERROR);
       DestroyWindow(hWnd);
       return FALSE;
   }

   // 창을 화면에 보이게 합니다.
   ShowWindow(hWnd, nCmdShow);

   // 창을 즉시 한 번 갱신하도록 요청합니다.
   UpdateWindow(hWnd);

   return TRUE;
}

// Windows가 창에 관한 메시지를 보낼 때 호출하는 함수입니다.
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_ERASEBKGND:
        // Windows의 기본 배경 지우기를 막습니다.
        // Direct2D가 직접 Clear하므로 기본 배경 지우기를 쓰면 깜빡임이 생길 수 있습니다.
        return 1;
    case WM_SIZE:
        // 창 크기가 바뀌면 새 클라이언트 영역 크기를 엔진에 알려줍니다.
        // LOWORD(lParam)은 너비, HIWORD(lParam)은 높이입니다.
        gGameEngine.Resize(LOWORD(lParam), HIWORD(lParam));
        break;
    case WM_COMMAND:
        {
            // 메뉴나 버튼 명령 ID를 꺼냅니다.
            int wmId = LOWORD(wParam);
            switch (wmId)
            {
            case IDM_ABOUT:
                // About 대화상자를 엽니다.
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                // 창을 닫습니다. 이후 WM_DESTROY 메시지가 옵니다.
                DestroyWindow(hWnd);
                break;
            default:
                // 우리가 처리하지 않는 메시지는 Windows 기본 처리에 맡깁니다.
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        // 렌더링은 게임 루프에서 직접 하므로 WM_PAINT에서는 그리지 않습니다.
        // ValidateRect는 "다시 그릴 필요 없음"이라고 Windows에 알려줍니다.
        ValidateRect(hWnd, nullptr);
        break;
    case WM_DESTROY:
        // 창이 파괴될 때 엔진 리소스를 정리합니다.
        gGameEngine.Shutdown();

        // 메시지 루프가 종료되도록 WM_QUIT 메시지를 보냅니다.
        PostQuitMessage(0);
        break;
    default:
        // 나머지 메시지는 Windows 기본 처리에 맡깁니다.
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

// About 대화상자 메시지 처리 함수입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);

    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }

    return (INT_PTR)FALSE;
}
