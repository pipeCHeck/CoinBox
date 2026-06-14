#pragma once

#include "UIElement.h"

class Canvas : public UIElement
{
public:
    enum class RenderMode
    {
        ScreenSpaceOverlay,
        WorldSpace
    };

    void SetRenderMode(RenderMode renderMode) { m_renderMode = renderMode; }
    RenderMode GetRenderMode() const { return m_renderMode; }

    void SetSortingOrder(int sortingOrder) { m_sortingOrder = sortingOrder; }
    int GetSortingOrder() const { return m_sortingOrder; }

    bool IsScreenSpaceUI() const override { return false; }
    int GetRenderOrder() const override { return m_sortingOrder * 10000; }

private:
    RenderMode m_renderMode = RenderMode::ScreenSpaceOverlay;
    int m_sortingOrder = 0;
};
