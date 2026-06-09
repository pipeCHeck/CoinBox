#include "framework.h"
#include "DemoScenes.h"

#include "GameObject.h"
#include "Input.h"

#include <cmath>
#include <memory>
#include <wrl/client.h>

using Microsoft::WRL::ComPtr;

namespace DemoGame
{
    class GridRenderer final : public Component
    {
    public:
        void Render(ID2D1DeviceContext* d2dContext) override
        {
            if (!d2dContext)
            {
                return;
            }

            ComPtr<ID2D1SolidColorBrush> brush;
            if (FAILED(d2dContext->CreateSolidColorBrush(
                D2D1::ColorF(0.24f, 0.29f, 0.36f, 0.55f),
                &brush)))
            {
                return;
            }

            const D2D1_SIZE_F size = d2dContext->GetSize();
            for (float x = 0.5f; x < size.width; x += 48.0f)
            {
                d2dContext->DrawLine(
                    D2D1::Point2F(x, 0.0f),
                    D2D1::Point2F(x, size.height),
                    brush.Get(),
                    1.0f);
            }

            for (float y = 0.5f; y < size.height; y += 48.0f)
            {
                d2dContext->DrawLine(
                    D2D1::Point2F(0.0f, y),
                    D2D1::Point2F(size.width, y),
                    brush.Get(),
                    1.0f);
            }
        }
    };

    class PlayerCircleRenderer final : public Component
    {
    public:
        void Update(float deltaSeconds) override
        {
            // Component는 자기 역할만 처리합니다. 여기서는 좌우 이동만 담당합니다.
            m_elapsedSeconds += deltaSeconds;

            Transform& transform = GetOwner()->GetTransform();

            const float speed = 320.0f;
            if (Input::IsKey(VK_LEFT))
            {
                transform.position.x -= speed * deltaSeconds;
            }
            if (Input::IsKey(VK_RIGHT))
            {
                transform.position.x += speed * deltaSeconds;
            }

            if (Input::IsMouseDown(MouseButton::Left))
            {
                const MousePosition mouse = Input::GetMousePosition();
                transform.position.x = mouse.x;
                transform.position.y = mouse.y;
            }
        }

        void Render(ID2D1DeviceContext* d2dContext) override
        {
            if (!d2dContext)
            {
                return;
            }

            Transform& transform = GetOwner()->GetTransform();
            const D2D1_SIZE_F size = d2dContext->GetSize();
            const float minX = 40.0f;
            const float maxX = size.width - 40.0f;
            transform.position.x = transform.position.x < minX ? minX : transform.position.x;
            transform.position.x = transform.position.x > maxX ? maxX : transform.position.x;

            ComPtr<ID2D1SolidColorBrush> brush;
            if (FAILED(d2dContext->CreateSolidColorBrush(
                D2D1::ColorF(0.18f, 0.64f, 0.96f),
                &brush)))
            {
                return;
            }

            const float baseY = transform.position.y > 0.0f
                ? transform.position.y
                : size.height * 0.62f;
            const float y = baseY + std::sin(m_elapsedSeconds * 3.0f) * 14.0f;
            const D2D1_ELLIPSE player = D2D1::Ellipse(
                D2D1::Point2F(transform.position.x, y),
                34.0f * transform.scale.x,
                34.0f * transform.scale.y);

            d2dContext->FillEllipse(player, brush.Get());
        }

    private:
        float m_elapsedSeconds = 0.0f;
    };

    void DemoBackgroundScene::OnUpdate(float deltaTime)
    {
        // 백그라운드 씬은 보통 저장 데이터, 전역 타이머, 리소스 상태 등을 갱신합니다.
        m_elapsedSeconds += deltaTime;
    }

    void DemoScene::OnInit()
    {
        // 씬을 만들 때는 GameObject를 만들고, 필요한 Component를 붙인 뒤, 씬에 추가합니다.
        auto grid = std::make_unique<GameObject>();
        grid->AddComponent<GridRenderer>();
        AddObject(std::move(grid));

        auto player = std::make_unique<GameObject>();
        player->GetTransform().position = Vector2(320.0f, 0.0f);
        player->GetTransform().scale = Vector2(1.0f, 1.0f);
        player->AddComponent<PlayerCircleRenderer>();
        AddObject(std::move(player));
    }

}