#pragma once

#include "Component.h"

#include <string>

// ResourceManager에 등록된 PNG 이미지를 GameObject의 Transform 위치에 그리는 컴포넌트입니다.
class SpriteRenderer : public Component
{
public:
    explicit SpriteRenderer(const std::wstring& bitmapKey);

    void Render(ID2D1DeviceContext* d2dContext) override;

private:
    std::wstring m_bitmapKey;
};
