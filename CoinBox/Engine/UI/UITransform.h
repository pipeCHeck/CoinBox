#pragma once

#include "Component.h"
#include "Vector2.h"

#include <d2d1_1.h>

class UITransform : public Component
{
public:
    void SetAnchorMin(const Vector2& anchorMin) { m_anchorMin = anchorMin; }
    const Vector2& GetAnchorMin() const { return m_anchorMin; }

    void SetAnchorMax(const Vector2& anchorMax) { m_anchorMax = anchorMax; }
    const Vector2& GetAnchorMax() const { return m_anchorMax; }

    void SetPivot(const Vector2& pivot) { m_pivot = pivot; }
    const Vector2& GetPivot() const { return m_pivot; }

    void SetSize(const Vector2& size) { m_size = size; }
    const Vector2& GetSize() const { return m_size; }

    void SetAnchoredPosition(const Vector2& anchoredPosition) { m_anchoredPosition = anchoredPosition; }
    const Vector2& GetAnchoredPosition() const { return m_anchoredPosition; }

    D2D1_RECT_F GetScreenRect() const;
    bool ContainsScreenPoint(const Vector2& point) const;

private:
    D2D1_RECT_F GetParentRect() const;

    Vector2 m_anchorMin = Vector2(0.0f, 0.0f);
    Vector2 m_anchorMax = Vector2(0.0f, 0.0f);
    Vector2 m_pivot = Vector2(0.0f, 0.0f);
    Vector2 m_size = Vector2(100.0f, 40.0f);
    Vector2 m_anchoredPosition = Vector2(0.0f, 0.0f);
};
