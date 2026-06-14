#pragma once

#include "UIElement.h"

#include <functional>

class UIButton : public UIElement
{
public:
    void Update(float deltaTime) override;

    bool IsHovered() const { return m_hovered; }
    bool IsPressed() const { return m_pressed; }

    std::function<void()> onClick;
    std::function<void()> onPressed;
    std::function<void()> onReleased;

private:
    bool m_hovered = false;
    bool m_pressed = false;
};
