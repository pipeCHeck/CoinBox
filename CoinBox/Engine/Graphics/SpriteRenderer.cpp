#include "SpriteRenderer.h"

#include "GameObject.h"
#include "ResourceManager.h"

SpriteRenderer::SpriteRenderer(const std::wstring& textureKey)
    : m_textureKey(textureKey)
{
}

void SpriteRenderer::SetSpriteSheet(int columns, int rows, int frameCount)
{
    m_columns = columns > 0 ? columns : 1;
    m_rows = rows > 0 ? rows : 1;
    m_frameCount = frameCount > 0 ? frameCount : m_columns * m_rows;
    SetFrame(m_frameIndex);
}

void SpriteRenderer::SetFrame(int frameIndex)
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

void SpriteRenderer::Render(ID2D1DeviceContext* d2dContext)
{
    if (!d2dContext || !m_visible)
    {
        return;
    }

    ID2D1Bitmap* texture = ResourceManager::GetTexture(m_textureKey);
    if (!texture)
    {
        return;
    }

    const Transform transform = GetOwner()->GetWorldTransform();
    const D2D1_SIZE_F textureSize = texture->GetSize();
    const float frameWidth = textureSize.width / static_cast<float>(m_columns);
    const float frameHeight = textureSize.height / static_cast<float>(m_rows);
    const int frame = m_frameCount > 0 ? m_frameIndex % m_frameCount : 0;
    const int sourceColumn = frame % m_columns;
    const int sourceRow = frame / m_columns;

    const Vector2 frameSize(frameWidth, frameHeight);
    const Vector2 drawSize = frameSize * transform.scale;
    const Vector2 topLeft = transform.position - ((frameSize / 2.0f + m_pivot) * transform.scale);

    const D2D1_RECT_F source = D2D1::RectF(
        sourceColumn * frameWidth,
        sourceRow * frameHeight,
        sourceColumn * frameWidth + frameWidth,
        sourceRow * frameHeight + frameHeight);

    const D2D1_RECT_F destination = D2D1::RectF(
        topLeft.x,
        topLeft.y,
        topLeft.x + drawSize.x,
        topLeft.y + drawSize.y);

    D2D1_MATRIX_3X2_F previousTransform;
    d2dContext->GetTransform(&previousTransform);
    const D2D1_POINT_2F pivot = D2D1::Point2F(transform.position.x, transform.position.y);
    d2dContext->SetTransform(D2D1::Matrix3x2F::Rotation(transform.rotation, pivot) * previousTransform);
    d2dContext->DrawBitmap(texture, destination, 1.0f, D2D1_INTERPOLATION_MODE_LINEAR, source);
    d2dContext->SetTransform(previousTransform);
}
