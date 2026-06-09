#include "ResourceManager.h"

#include <mmsystem.h>

#pragma comment(lib, "windowscodecs.lib")
#pragma comment(lib, "winmm.lib")

using Microsoft::WRL::ComPtr;

ID2D1DeviceContext* ResourceManager::m_d2dContext = nullptr;
ComPtr<IWICImagingFactory> ResourceManager::m_wicFactory;
std::wstring ResourceManager::m_assetRoot = L"Assets";
std::unordered_map<std::wstring, std::wstring> ResourceManager::m_texturePaths;
std::unordered_map<std::wstring, ComPtr<ID2D1Bitmap>> ResourceManager::m_textures;
std::unordered_map<std::wstring, std::wstring> ResourceManager::m_audioPaths;

HRESULT ResourceManager::Initialize(ID2D1DeviceContext* d2dContext)
{
    m_d2dContext = d2dContext;

    if (m_wicFactory)
    {
        return S_OK;
    }

    return CoCreateInstance(
        CLSID_WICImagingFactory,
        nullptr,
        CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(&m_wicFactory));
}

void ResourceManager::Shutdown()
{
    StopAudio();
    ClearTextures();
    m_texturePaths.clear();
    m_audioPaths.clear();
    m_wicFactory.Reset();
    m_d2dContext = nullptr;
}

void ResourceManager::SetAssetRoot(const std::wstring& assetRoot)
{
    m_assetRoot = assetRoot;
}

std::wstring ResourceManager::GetAssetRoot()
{
    return m_assetRoot;
}

std::wstring ResourceManager::MakeAssetPath(const std::wstring& relativePath)
{
    if (m_assetRoot.empty())
    {
        return relativePath;
    }

    const wchar_t last = m_assetRoot[m_assetRoot.size() - 1];
    if (last == L'\\' || last == L'/')
    {
        return m_assetRoot + relativePath;
    }

    return m_assetRoot + L"\\" + relativePath;
}

HRESULT ResourceManager::LoadTexture(const std::wstring& key, const std::wstring& relativePath)
{
    m_texturePaths[key] = relativePath;

    if (!m_d2dContext || !m_wicFactory)
    {
        return E_FAIL;
    }

    const auto existing = m_textures.find(key);
    if (existing != m_textures.end())
    {
        return S_OK;
    }

    const std::wstring fullPath = MakeAssetPath(relativePath);

    ComPtr<IWICBitmapDecoder> decoder;
    HRESULT hr = m_wicFactory->CreateDecoderFromFilename(
        fullPath.c_str(),
        nullptr,
        GENERIC_READ,
        WICDecodeMetadataCacheOnLoad,
        &decoder);

    ComPtr<IWICBitmapFrameDecode> frame;
    if (SUCCEEDED(hr))
    {
        hr = decoder->GetFrame(0, &frame);
    }

    ComPtr<IWICFormatConverter> converter;
    if (SUCCEEDED(hr))
    {
        hr = m_wicFactory->CreateFormatConverter(&converter);
    }

    if (SUCCEEDED(hr))
    {
        hr = converter->Initialize(
            frame.Get(),
            GUID_WICPixelFormat32bppPBGRA,
            WICBitmapDitherTypeNone,
            nullptr,
            0.0f,
            WICBitmapPaletteTypeMedianCut);
    }

    ComPtr<ID2D1Bitmap> texture;
    if (SUCCEEDED(hr))
    {
        hr = m_d2dContext->CreateBitmapFromWicBitmap(converter.Get(), nullptr, &texture);
    }

    if (SUCCEEDED(hr))
    {
        m_textures[key] = texture;
    }

    return hr;
}

ID2D1Bitmap* ResourceManager::GetTexture(const std::wstring& key)
{
    const auto found = m_textures.find(key);
    if (found != m_textures.end())
    {
        return found->second.Get();
    }

    const auto foundPath = m_texturePaths.find(key);
    if (foundPath == m_texturePaths.end())
    {
        return nullptr;
    }

    if (FAILED(LoadTexture(key, foundPath->second)))
    {
        return nullptr;
    }

    const auto reloaded = m_textures.find(key);
    return reloaded != m_textures.end() ? reloaded->second.Get() : nullptr;
}

void ResourceManager::ClearTextures()
{
    m_textures.clear();
}

void ResourceManager::LoadAudio(const std::wstring& key, const std::wstring& relativePath)
{
    m_audioPaths[key] = MakeAssetPath(relativePath);
}

bool ResourceManager::PlayAudio(const std::wstring& key, bool loop)
{
    const auto found = m_audioPaths.find(key);
    if (found == m_audioPaths.end())
    {
        return false;
    }

    DWORD flags = SND_FILENAME | SND_ASYNC | SND_NODEFAULT;
    if (loop)
    {
        flags |= SND_LOOP;
    }

    return PlaySoundW(found->second.c_str(), nullptr, flags) == TRUE;
}

void ResourceManager::StopAudio()
{
    PlaySoundW(nullptr, nullptr, 0);
}
