#pragma once

#include "Component.h"

class Canvas;

class UIElement : public Component
{
public:
    void SetVisible(bool visible) { m_visible = visible; }
    bool IsVisible() const { return m_visible; }

    void SetInteractable(bool interactable) { m_interactable = interactable; }
    bool IsInteractable() const { return m_interactable; }

    void SetRaycastTarget(bool raycastTarget) { m_raycastTarget = raycastTarget; }
    bool IsRaycastTarget() const { return m_raycastTarget; }

    void SetOpacity(float opacity) { m_opacity = Clamp01(opacity); }
    float GetOpacity() const { return m_opacity; }

    void SetRenderOrder(int renderOrder) { m_renderOrder = renderOrder; }
    int GetLocalRenderOrder() const { return m_renderOrder; }
    int GetRenderOrder() const override;

    bool IsScreenSpaceUI() const override;
    Canvas* GetCanvas() const;

private:
    bool m_visible = true;
    bool m_interactable = true;
    bool m_raycastTarget = true;
    float m_opacity = 1.0f;
    int m_renderOrder = 0;
};
