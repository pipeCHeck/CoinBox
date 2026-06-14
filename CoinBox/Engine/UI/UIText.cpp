#include "UIText.h"

#include "GameObject.h"
#include "UITransform.h"

using Microsoft::WRL::ComPtr;

UIText::UIText(const std::wstring& text)
    : m_text(text)
{
}

void UIText::Render(ID2D1DeviceContext* d2dContext)
{
    if (!d2dContext || !IsVisible() || m_text.empty() || !EnsureTextFormat())
    {
        return;
    }

    UITransform* transform = GetOwner() ? GetOwner()->GetComponent<UITransform>() : nullptr;
    if (!transform)
    {
        return;
    }

    ComPtr<ID2D1SolidColorBrush> brush;
    if (FAILED(d2dContext->CreateSolidColorBrush(m_color, &brush)))
    {
        return;
    }

    brush->SetOpacity(GetOpacity() * m_color.a);
    d2dContext->DrawTextW(
        m_text.c_str(),
        static_cast<UINT32>(m_text.size()),
        m_textFormat.Get(),
        transform->GetScreenRect(),
        brush.Get());
}

void UIText::SetFontFamily(const std::wstring& fontFamily)
{
    m_fontFamily = fontFamily;
    m_formatDirty = true;
}

void UIText::SetFontSize(float fontSize)
{
    m_fontSize = fontSize > 0.0f ? fontSize : 1.0f;
    m_formatDirty = true;
}

void UIText::SetTextAlignment(DWRITE_TEXT_ALIGNMENT alignment)
{
    m_textAlignment = alignment;
    if (m_textFormat)
    {
        m_textFormat->SetTextAlignment(m_textAlignment);
    }
}

void UIText::SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT alignment)
{
    m_paragraphAlignment = alignment;
    if (m_textFormat)
    {
        m_textFormat->SetParagraphAlignment(m_paragraphAlignment);
    }
}

bool UIText::EnsureTextFormat()
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
