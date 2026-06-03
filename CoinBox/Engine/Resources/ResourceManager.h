#pragma once

#include <d2d1_1.h>
#include <wincodec.h>
#include <wrl/client.h>

#include <string>
#include <unordered_map>

// 리소스 위치와 로딩을 한 곳에서 관리하는 클래스입니다.
//
// 사용 흐름:
// 1. 엔진 시작 시 Initialize로 D2D 장치와 WIC를 준비합니다.
// 2. SetAssetRoot로 Assets 폴더 위치를 정합니다.
// 3. LoadBitmap / LoadAudio로 파일을 키 이름과 함께 등록합니다.
// 4. GetBitmap / PlayAudio로 등록된 리소스를 사용합니다.
class ResourceManager
{
public:
    static HRESULT Initialize(ID2D1DeviceContext* d2dContext);
    static void Shutdown();

    static void SetAssetRoot(const std::wstring& assetRoot);
    static std::wstring GetAssetRoot();
    static std::wstring MakeAssetPath(const std::wstring& relativePath);

    static HRESULT LoadBitmap(const std::wstring& key, const std::wstring& relativePath);
    static ID2D1Bitmap* GetBitmap(const std::wstring& key);
    static void ClearBitmaps();

    static void LoadAudio(const std::wstring& key, const std::wstring& relativePath);
    static bool PlayAudio(const std::wstring& key, bool loop = false);
    static void StopAudio();

private:
    static ID2D1DeviceContext* m_d2dContext;
    static Microsoft::WRL::ComPtr<IWICImagingFactory> m_wicFactory;
    static std::wstring m_assetRoot;
    static std::unordered_map<std::wstring, std::wstring> m_bitmapPaths;
    static std::unordered_map<std::wstring, Microsoft::WRL::ComPtr<ID2D1Bitmap>> m_bitmaps;
    static std::unordered_map<std::wstring, std::wstring> m_audioPaths;
};
