#include "UIPanel.h"

#include "GameObject.h"
#include "UITransform.h"

#include <wrl/client.h>

void UIPanel::Render(ID2D1DeviceContext* d2dContext)
{
    if (!d2dContext || !IsVisible())
    {
        return;
    }

    UITransform* transform = GetOwner() ? GetOwner()->GetComponent<UITransform>() : nullptr;
    if (!transform)
    {
        return;
    }

    const D2D1_RECT_F rect = transform->GetScreenRect();
    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> brush;

    if (SUCCEEDED(d2dContext->CreateSolidColorBrush(m_backgroundColor, &brush)))
    {
        brush->SetOpacity(GetOpacity() * m_backgroundColor.a);
        d2dContext->FillRectangle(rect, brush.Get());
    }

    if (m_borderThickness > 0.0f && SUCCEEDED(d2dContext->CreateSolidColorBrush(m_borderColor, &brush)))
    {
        brush->SetOpacity(GetOpacity() * m_borderColor.a);
        d2dContext->DrawRectangle(rect, brush.Get(), m_borderThickness);
    }
}
