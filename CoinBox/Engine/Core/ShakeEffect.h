#pragma once

#include "Component.h"

#include <random>

class ShakeEffect : public Component
{
public:
    ShakeEffect();
    ~ShakeEffect() override;

    void Update(float deltaTime) override;

    void Play(float duration, float strength);
    void Play(float duration, const Vector2& strength, float rotationStrength = 0.0f);
    void Stop();

    void SetFadeOut(bool fadeOut) { m_fadeOut = fadeOut; }
    bool GetFadeOut() const { return m_fadeOut; }

    bool IsPlaying() const { return m_playing; }

private:
    void RemovePreviousOffset();
    float RandomRange(float minValue, float maxValue);

    std::mt19937 m_rng;
    Vector2 m_strength = Vector2(0.0f, 0.0f);
    Vector2 m_previousOffset = Vector2(0.0f, 0.0f);
    float m_rotationStrength = 0.0f;
    float m_previousRotation = 0.0f;
    float m_duration = 0.0f;
    float m_remaining = 0.0f;
    bool m_fadeOut = true;
    bool m_playing = false;
};
