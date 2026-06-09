#include "SpriteRenderer.h"

#include "GameObject.h"
#include "ResourceManager.h"

SpriteRenderer::SpriteRenderer(const std::wstring& textureKey)
    : m_textureKey(textureKey)
{
}

void SpriteRenderer::Render(ID2D1DeviceContext* d2dContext)
{
    if (!d2dContext)
    {
        return;
    }

    ID2D1Bitmap* texture = ResourceManager::GetTexture(m_textureKey);
    if (!texture)
    {
        return;
    }

    const Transform& transform = GetOwner()->GetTransform();
    const D2D1_SIZE_F textureSize = texture->GetSize();

    const D2D1_RECT_F destination = D2D1::RectF(
        transform.position.x,
        transform.position.y,
        transform.position.x + textureSize.width * transform.scale.x,
        transform.position.y + textureSize.height * transform.scale.y);

    d2dContext->DrawBitmap(texture, destination);
}
