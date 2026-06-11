#pragma once

#include "Component.h"
#include "Vector2.h"

#include <dwrite.h>
#include <string>
#include <wrl/client.h>

class TextRenderer : public Component
{
public:
    TextRenderer() = default;
    explicit TextRenderer(const std::wstring& text);

    void Render(ID2D1DeviceContext* d2dContext) override;

    void SetText(const std::wstring& text) { m_text = text; }
    const std::wstring& GetText() const { return m_text; }

    void SetFontFamily(const std::wstring& fontFamily);
    const std::wstring& GetFontFamily() const { return m_fontFamily; }

    void SetFontSize(float fontSize);
    float GetFontSize() const { return m_fontSize; }

    void SetBoxSize(const Vector2& boxSize) { m_boxSize = boxSize; }
    const Vector2& GetBoxSize() const { return m_boxSize; }

    void SetPivot(const Vector2& pivot) { m_pivot = pivot; }
    const Vector2& GetPivot() const { return m_pivot; }

    void SetColor(const D2D1_COLOR_F& color) { m_color = color; }
    const D2D1_COLOR_F& GetColor() const { return m_color; }

    void SetOpacity(float opacity) { m_opacity = opacity; }
    float GetOpacity() const { return m_opacity; }

    void SetTextAlignment(DWRITE_TEXT_ALIGNMENT alignment);
    void SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT alignment);

    void SetVisible(bool visible) { m_visible = visible; }
    bool IsVisible() const { return m_visible; }

    void SetRenderOrder(int order) { m_renderOrder = order; }
    int GetRenderOrder() const override { return m_renderOrder; }

private:
    bool EnsureTextFormat();

    Microsoft::WRL::ComPtr<IDWriteFactory> m_dwriteFactory;
    Microsoft::WRL::ComPtr<IDWriteTextFormat> m_textFormat;
    std::wstring m_text;
    std::wstring m_fontFamily = L"Segoe UI";
    Vector2 m_boxSize = Vector2(320.0f, 64.0f);
    Vector2 m_pivot = Vector2(0.0f, 0.0f);
    D2D1_COLOR_F m_color = D2D1::ColorF(0.93f, 0.95f, 0.98f, 1.0f);
    DWRITE_TEXT_ALIGNMENT m_textAlignment = DWRITE_TEXT_ALIGNMENT_LEADING;
    DWRITE_PARAGRAPH_ALIGNMENT m_paragraphAlignment = DWRITE_PARAGRAPH_ALIGNMENT_NEAR;
    float m_fontSize = 24.0f;
    float m_opacity = 1.0f;
    int m_renderOrder = 0;
    bool m_visible = true;
    bool m_formatDirty = true;
};
