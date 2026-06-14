#include "UIElement.h"

#include "Canvas.h"
#include "GameObject.h"

Canvas* UIElement::GetCanvas() const
{
    GameObject* current = GetOwner();
    while (current)
    {
        if (Canvas* canvas = current->GetComponent<Canvas>())
        {
            return canvas;
        }

        current = current->GetParent();
    }

    return nullptr;
}

int UIElement::GetRenderOrder() const
{
    Canvas* canvas = GetCanvas();
    const int canvasOrder = canvas ? canvas->GetSortingOrder() * 10000 : 0;
    return canvasOrder + m_renderOrder;
}

bool UIElement::IsScreenSpaceUI() const
{
    Canvas* canvas = GetCanvas();
    return !canvas || canvas->GetRenderMode() == Canvas::RenderMode::ScreenSpaceOverlay;
}
