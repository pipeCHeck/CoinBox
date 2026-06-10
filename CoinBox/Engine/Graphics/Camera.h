#pragma once

#include "Component.h"
#include "Vector2.h"

#include <d2d1_1.h>

class Camera : public Component
{
public:
    float GetZoom() const { return m_zoom; }
    void SetZoom(float zoom) { m_zoom = zoom > 0.01f ? zoom : 0.01f; }

    Vector2 GetOffset() const { return m_offset; }
    void SetOffset(const Vector2& offset) { m_offset = offset; }

    D2D1_MATRIX_3X2_F GetViewMatrix(const D2D1_SIZE_F& viewportSize) const;

private:
    float m_zoom = 1.0f;
    Vector2 m_offset = Vector2(0.0f, 0.0f);
};
