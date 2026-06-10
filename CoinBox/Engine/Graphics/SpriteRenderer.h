#pragma once

#include "Component.h"
#include "Vector2.h"

#include <string>

// ResourceManager에 등록된 텍스처를 owner의 월드 Transform 기준으로 그립니다.
// 피벗, 회전, 스프라이트시트 프레임, 표시 여부, 렌더 순서를 지원합니다.
class SpriteRenderer : public Component
{
public:
    explicit SpriteRenderer(const std::wstring& textureKey);

    void SetTextureKey(const std::wstring& textureKey) { m_textureKey = textureKey; }
    const std::wstring& GetTextureKey() const { return m_textureKey; }

    // columns/rows는 시트의 칸 수입니다. frameCount는 columns * rows보다 작아도 됩니다.
    void SetSpriteSheet(int columns, int rows, int frameCount = 0);
    void SetFrame(int frameIndex);
    int GetFrame() const { return m_frameIndex; }

    // pivot은 원본 이미지 중심에서 피벗까지의 픽셀 오프셋입니다.
    void SetPivot(const Vector2& pivot) { m_pivot = pivot; }
    const Vector2& GetPivot() const { return m_pivot; }

    void SetVisible(bool visible) { m_visible = visible; }
    bool IsVisible() const { return m_visible; }

    // 값이 클수록 나중에 그려지므로 화면 앞쪽에 보입니다.
    void SetRenderOrder(int order) { m_renderOrder = order; }
    int GetRenderOrder() const override { return m_renderOrder; }

    void Render(ID2D1DeviceContext* d2dContext) override;

private:
    std::wstring m_textureKey;
    Vector2 m_pivot = Vector2(0.0f, 0.0f);
    int m_columns = 1;
    int m_rows = 1;
    int m_frameCount = 1;
    int m_frameIndex = 0;
    int m_renderOrder = 0;
    bool m_visible = true;
};
