#pragma once

#include "UIElement.h"
#include "Vector2.h"

#include <dwrite.h>
#include <string>
#include <wrl/client.h>

class UIText : public UIElement
{
public:
    UIText() = default;
    explicit UIText(const std::wstring& text);

    void SetText(const std::wstring& text) { m_text = text; }
    const std::wstring& GetText() const { return m_text; }

    void SetFontFamily(const std::wstring& fontFamily);
    const std::wstring& GetFontFamily() const { return m_fontFamily; }

    void SetFontSize(float fontSize);
    float GetFontSize() const { return m_fontSize; }

    void SetColor(const D2D1_COLOR_F& color) { m_color = color; }
    const D2D1_COLOR_F& GetColor() const { return m_color; }

    void SetTextAlignment(DWRITE_TEXT_ALIGNMENT alignment);
    void SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT alignment);

    void Render(ID2D1DeviceContext* d2dContext) override;

private:
    bool EnsureTextFormat();

    Microsoft::WRL::ComPtr<IDWriteFactory> m_dwriteFactory;
    Microsoft::WRL::ComPtr<IDWriteTextFormat> m_textFormat;
    std::wstring m_text;
    std::wstring m_fontFamily = L"Segoe UI";
    D2D1_COLOR_F m_color = D2D1::ColorF(0.93f, 0.95f, 0.98f, 1.0f);
    DWRITE_TEXT_ALIGNMENT m_textAlignment = DWRITE_TEXT_ALIGNMENT_LEADING;
    DWRITE_PARAGRAPH_ALIGNMENT m_paragraphAlignment = DWRITE_PARAGRAPH_ALIGNMENT_NEAR;
    float m_fontSize = 24.0f;
    bool m_formatDirty = true;
};
