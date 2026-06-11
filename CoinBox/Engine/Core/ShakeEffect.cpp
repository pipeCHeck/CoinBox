#include "ShakeEffect.h"

#include "GameObject.h"

ShakeEffect::ShakeEffect()
    : m_rng(std::random_device{}())
{
}

ShakeEffect::~ShakeEffect()
{
    RemovePreviousOffset();
}

void ShakeEffect::Update(float deltaTime)
{
    if (!m_playing)
    {
        return;
    }

    RemovePreviousOffset();

    m_remaining -= deltaTime;
    if (m_remaining <= 0.0f)
    {
        m_playing = false;
        m_remaining = 0.0f;
        return;
    }

    float power = 1.0f;
    if (m_fadeOut && m_duration > 0.0f)
    {
        power = m_remaining / m_duration;
    }

    m_previousOffset = Vector2(
        RandomRange(-m_strength.x, m_strength.x) * power,
        RandomRange(-m_strength.y, m_strength.y) * power);
    m_previousRotation = RandomRange(-m_rotationStrength, m_rotationStrength) * power;

    if (GameObject* owner = GetOwner())
    {
        owner->GetAniTransform().position = owner->GetAniTransform().position + m_previousOffset;
        owner->GetAniTransform().rotation += m_previousRotation;
    }
}

void ShakeEffect::Play(float duration, float strength)
{
    Play(duration, Vector2(strength, strength), 0.0f);
}

void ShakeEffect::Play(float duration, const Vector2& strength, float rotationStrength)
{
    RemovePreviousOffset();

    m_duration = duration > 0.0f ? duration : 0.0f;
    m_remaining = m_duration;
    m_strength = strength;
    m_rotationStrength = rotationStrength;
    m_playing = m_duration > 0.0f;
}

void ShakeEffect::Stop()
{
    RemovePreviousOffset();
    m_remaining = 0.0f;
    m_playing = false;
}

void ShakeEffect::RemovePreviousOffset()
{
    if (GameObject* owner = GetOwner())
    {
        owner->GetAniTransform().position = owner->GetAniTransform().position - m_previousOffset;
        owner->GetAniTransform().rotation -= m_previousRotation;
    }

    m_previousOffset = Vector2(0.0f, 0.0f);
    m_previousRotation = 0.0f;
}

float ShakeEffect::RandomRange(float minValue, float maxValue)
{
    std::uniform_real_distribution<float> distribution(minValue, maxValue);
    return distribution(m_rng);
}
