#pragma once

#include "Scene.h"

namespace DemoGame
{
    class DemoBackgroundScene final : public BackgroundScene
    {
    protected:
        void OnUpdate(float deltaTime) override;

    private:
        float m_elapsedSeconds = 0.0f;
    };

    class DemoScene final : public ForegroundScene
    {
    protected:
        void OnInit() override;
    };
}