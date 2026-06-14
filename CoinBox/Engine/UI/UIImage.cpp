#include "UIImage.h"

#include "GameObject.h"
#include "ResourceManager.h"
#include "UITransform.h"

#include <wrl/client.h>

UIImage::UIImage(const std::wstring& textureKey)
    : m_textureKey(textureKey)
{
}

void UIImage::SetSpriteSheet(int columns, int rows, int frameCount)
{
    m_columns = columns > 0 ? columns : 1;
    m_rows = rows > 0 ? rows : 1;
    m_frameCount = frameCount > 0 ? frameCount : m_columns * m_rows;
    SetFrame(m_frameIndex);
}

void UIImage::SetFrame(int frameIndex)
{
    if (m_frameCount <= 0)
    {
        m_frameIndex = 0;
        return;
    }

    m_frameIndex = frameIndex % m_frameCount;
    if (m_frameIndex < 0)
    {
        m_frameIndex += m_frameCount;
    }
}

void UIImage::Render(ID2D1DeviceContext* d2dContext)
{
    if (!d2dContext || !IsVisible())
    {
        return;
    }

    UITransform* transform = GetOwner() ? GetOwner()->GetComponent<UITransform>() : nullptr;
    if (!transform)
    {
        return;
    }

    const D2D1_RECT_F destination = transform->GetScreenRect();
    ID2D1Bitmap* texture = ResourceManager::GetTexture(m_textureKey);

    if (!texture)
    {
        Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> brush;
        if (SUCCEEDED(d2dContext->CreateSolidColorBrush(m_color, &brush)))
        {
            brush->SetOpacity(GetOpacity() * m_color.a);
            d2dContext->FillRectangle(destination, brush.Get());
        }

        return;
    }

    const D2D1_SIZE_F textureSize = texture->GetSize();
    const float frameWidth = textureSize.width / static_cast<float>(m_columns);
    const float frameHeight = textureSize.height / static_cast<float>(m_rows);
    const int frame = m_frameCount > 0 ? m_frameIndex % m_frameCount : 0;
    const int sourceColumn = frame % m_columns;
    const int sourceRow = frame / m_columns;

    const D2D1_RECT_F source = D2D1::RectF(
        sourceColumn * frameWidth,
        sourceRow * frameHeight,
        sourceColumn * frameWidth + frameWidth,
        sourceRow * frameHeight + frameHeight);

    d2dContext->DrawBitmap(texture, destination, GetOpacity() * m_color.a, D2D1_INTERPOLATION_MODE_LINEAR, source);
}
