#include "TextRenderer.h"

#include "GameObject.h"

using Microsoft::WRL::ComPtr;

TextRenderer::TextRenderer(const std::wstring& text)
    : m_text(text)
{
}

void TextRenderer::Render(ID2D1DeviceContext* d2dContext)
{
    if (!d2dContext || !m_visible || m_text.empty() || !EnsureTextFormat())
    {
        return;
    }

    ComPtr<ID2D1SolidColorBrush> brush;
    if (FAILED(d2dContext->CreateSolidColorBrush(m_color, &brush)))
    {
        return;
    }

    brush->SetOpacity(m_opacity);

    const Transform transform = GetOwner()->GetWorldTransform();
    const Vector2 drawSize = m_boxSize * transform.scale;
    const Vector2 topLeft = transform.position - (m_pivot * transform.scale);

    const D2D1_RECT_F destination = D2D1::RectF(
        topLeft.x,
        topLeft.y,
        topLeft.x + drawSize.x,
        topLeft.y + drawSize.y);

    D2D1_MATRIX_3X2_F previousTransform;
    d2dContext->GetTransform(&previousTransform);
    const D2D1_POINT_2F pivot = D2D1::Point2F(transform.position.x, transform.position.y);
    d2dContext->SetTransform(D2D1::Matrix3x2F::Rotation(transform.rotation, pivot) * previousTransform);
    d2dContext->DrawTextW(
        m_text.c_str(),
        static_cast<UINT32>(m_text.size()),
        m_textFormat.Get(),
        destination,
        brush.Get());
    d2dContext->SetTransform(previousTransform);
}

void TextRenderer::SetFontFamily(const std::wstring& fontFamily)
{
    m_fontFamily = fontFamily;
    m_formatDirty = true;
}

void TextRenderer::SetFontSize(float fontSize)
{
    m_fontSize = fontSize > 0.0f ? fontSize : 1.0f;
    m_formatDirty = true;
}

void TextRenderer::SetTextAlignment(DWRITE_TEXT_ALIGNMENT alignment)
{
    m_textAlignment = alignment;
    if (m_textFormat)
    {
        m_textFormat->SetTextAlignment(m_textAlignment);
    }
}

void TextRenderer::SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT alignment)
{
    m_paragraphAlignment = alignment;
    if (m_textFormat)
    {
        m_textFormat->SetParagraphAlignment(m_paragraphAlignment);
    }
}

bool TextRenderer::EnsureTextFormat()
{
    if (!m_dwriteFactory)
    {
        const HRESULT hr = DWriteCreateFactory(
            DWRITE_FACTORY_TYPE_SHARED,
            __uuidof(IDWriteFactory),
            reinterpret_cast<IUnknown**>(m_dwriteFactory.GetAddressOf()));

        if (FAILED(hr))
        {
            return false;
        }
    }

    if (m_textFormat && !m_formatDirty)
    {
        return true;
    }

    m_textFormat.Reset();
    HRESULT hr = m_dwriteFactory->CreateTextFormat(
        m_fontFamily.c_str(),
        nullptr,
        DWRITE_FONT_WEIGHT_NORMAL,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        m_fontSize,
        L"ko-kr",
        &m_textFormat);

    if (FAILED(hr))
    {
        return false;
    }

    m_textFormat->SetTextAlignment(m_textAlignment);
    m_textFormat->SetParagraphAlignment(m_paragraphAlignment);
    m_formatDirty = false;
    return true;
}
