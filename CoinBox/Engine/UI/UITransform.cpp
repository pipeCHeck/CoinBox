#include "UITransform.h"

#include "GameObject.h"
#include "Screen.h"

D2D1_RECT_F UITransform::GetScreenRect() const
{
    const D2D1_RECT_F parentRect = GetParentRect();
    const Vector2 parentPosition(parentRect.left, parentRect.top);
    const Vector2 parentSize(parentRect.right - parentRect.left, parentRect.bottom - parentRect.top);

    const Vector2 anchorTopLeft = parentPosition + parentSize * m_anchorMin;
    const Vector2 anchorBottomRight = parentPosition + parentSize * m_anchorMax;
    const Vector2 anchorSize = anchorBottomRight - anchorTopLeft;

    Vector2 finalSize = m_size;
    if (m_anchorMin.x != m_anchorMax.x || m_anchorMin.y != m_anchorMax.y)
    {
        finalSize = anchorSize + m_size;
    }

    const Vector2 topLeft = anchorTopLeft + m_anchoredPosition - (finalSize * m_pivot);

    return D2D1::RectF(
        topLeft.x,
        topLeft.y,
        topLeft.x + finalSize.x,
        topLeft.y + finalSize.y);
}

bool UITransform::ContainsScreenPoint(const Vector2& point) const
{
    const D2D1_RECT_F rect = GetScreenRect();
    return point.x >= rect.left
        && point.x <= rect.right
        && point.y >= rect.top
        && point.y <= rect.bottom;
}

D2D1_RECT_F UITransform::GetParentRect() const
{
    GameObject* owner = GetOwner();
    GameObject* parent = owner ? owner->GetParent() : nullptr;

    while (parent)
    {
        if (UITransform* parentTransform = parent->GetComponent<UITransform>())
        {
            return parentTransform->GetScreenRect();
        }

        parent = parent->GetParent();
    }

    return D2D1::RectF(0.0f, 0.0f, Screen::GetWidth(), Screen::GetHeight());
}
