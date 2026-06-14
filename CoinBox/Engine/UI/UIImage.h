#pragma once

#include "UIElement.h"

#include <d2d1_1.h>
#include <string>

class UIImage : public UIElement
{
public:
    UIImage() = default;
    explicit UIImage(const std::wstring& textureKey);

    void SetTextureKey(const std::wstring& textureKey) { m_textureKey = textureKey; }
    const std::wstring& GetTextureKey() const { return m_textureKey; }

    void SetColor(const D2D1_COLOR_F& color) { m_color = color; }
    const D2D1_COLOR_F& GetColor() const { return m_color; }

    void SetSpriteSheet(int columns, int rows, int frameCount = 0);
    void SetFrame(int frameIndex);
    int GetFrame() const { return m_frameIndex; }

    void Render(ID2D1DeviceContext* d2dContext) override;

private:
    std::wstring m_textureKey;
    D2D1_COLOR_F m_color = D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f);
    int m_columns = 1;
    int m_rows = 1;
    int m_frameCount = 1;
    int m_frameIndex = 0;
};
