#include "SpriteRenderer.h"

#include "GameObject.h"
#include "ResourceManager.h"

SpriteRenderer::SpriteRenderer(const std::wstring& bitmapKey)
    : m_bitmapKey(bitmapKey)
{
}

void SpriteRenderer::Render(ID2D1DeviceContext* d2dContext)
{
    if (!d2dContext)
    {
        return;
    }

    ID2D1Bitmap* bitmap = ResourceManager::GetBitmap(m_bitmapKey);
    if (!bitmap)
    {
        return;
    }

    const Transform& transform = GetOwner()->GetTransform();
    const D2D1_SIZE_F bitmapSize = bitmap->GetSize();

    const D2D1_RECT_F destination = D2D1::RectF(
        transform.position.x,
        transform.position.y,
        transform.position.x + bitmapSize.width * transform.scale.x,
        transform.position.y + bitmapSize.height * transform.scale.y);

    d2dContext->DrawBitmap(bitmap, destination);
}
