#include "UIButton.h"

#include "GameObject.h"
#include "Input.h"
#include "UITransform.h"

void UIButton::Update(float deltaTime)
{
    (void)deltaTime;

    if (!IsVisible() || !IsInteractable() || !IsRaycastTarget())
    {
        m_hovered = false;
        m_pressed = false;
        return;
    }

    UITransform* transform = GetOwner() ? GetOwner()->GetComponent<UITransform>() : nullptr;
    if (!transform)
    {
        m_hovered = false;
        m_pressed = false;
        return;
    }

    m_hovered = transform->ContainsScreenPoint(Input::GetMousePosition());

    if (m_hovered && Input::IsMouseDown(MouseButton::Left))
    {
        m_pressed = true;
        if (onPressed)
        {
            onPressed();
        }
    }

    if (m_pressed && Input::IsMouseUp(MouseButton::Left))
    {
        const bool clicked = m_hovered;
        m_pressed = false;

        if (onReleased)
        {
            onReleased();
        }

        if (clicked && onClick)
        {
            onClick();
        }
    }
}
