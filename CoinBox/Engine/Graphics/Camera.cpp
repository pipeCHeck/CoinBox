#include "Camera.h"

#include "GameObject.h"

D2D1_MATRIX_3X2_F Camera::GetViewMatrix(const D2D1_SIZE_F& viewportSize) const
{
    const Transform cameraTransform = GetOwner()
        ? GetOwner()->GetWorldTransform()
        : Transform();

    const D2D1_POINT_2F origin = D2D1::Point2F(0.0f, 0.0f);
    const float centerX = viewportSize.width * 0.5f + m_offset.x;
    const float centerY = viewportSize.height * 0.5f + m_offset.y;

    return
        D2D1::Matrix3x2F::Translation(-cameraTransform.position.x, -cameraTransform.position.y) *
        D2D1::Matrix3x2F::Rotation(-cameraTransform.rotation, origin) *
        D2D1::Matrix3x2F::Scale(m_zoom, m_zoom, origin) *
        D2D1::Matrix3x2F::Translation(centerX, centerY);
}
