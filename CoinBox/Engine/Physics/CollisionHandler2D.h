#pragma once

#include "Collision2D.h"
#include "Component.h"

#include <functional>

class CollisionHandler2D : public Component
{
public:
    using Callback = std::function<void(const Collision2D&)>;

    void SetOnCollisionEnter(Callback callback) { m_onEnter = callback; }
    void SetOnCollisionStay(Callback callback) { m_onStay = callback; }
    void SetOnCollisionExit(Callback callback) { m_onExit = callback; }

    void OnCollisionEnter2D(const Collision2D& collision) override;
    void OnCollisionStay2D(const Collision2D& collision) override;
    void OnCollisionExit2D(const Collision2D& collision) override;

private:
    Callback m_onEnter;
    Callback m_onStay;
    Callback m_onExit;
};
