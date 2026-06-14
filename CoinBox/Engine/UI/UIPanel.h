#pragma once

#include "UIElement.h"

#include <d2d1_1.h>

class UIPanel : public UIElement
{
public:
    void SetBackgroundColor(const D2D1_COLOR_F& color) { m_backgroundColor = color; }
    const D2D1_COLOR_F& GetBackgroundColor() const { return m_backgroundColor; }

    void SetBorderColor(const D2D1_COLOR_F& color) { m_borderColor = color; }
    const D2D1_COLOR_F& GetBorderColor() const { return m_borderColor; }

    void SetBorderThickness(float thickness) { m_borderThickness = thickness > 0.0f ? thickness : 0.0f; }
    float GetBorderThickness() const { return m_borderThickness; }

    void Render(ID2D1DeviceContext* d2dContext) override;

private:
    D2D1_COLOR_F m_backgroundColor = D2D1::ColorF(0.05f, 0.06f, 0.08f, 0.85f);
    D2D1_COLOR_F m_borderColor = D2D1::ColorF(1.0f, 1.0f, 1.0f, 0.18f);
    float m_borderThickness = 0.0f;
};
