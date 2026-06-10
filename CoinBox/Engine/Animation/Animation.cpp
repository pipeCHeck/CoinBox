#include "Animation.h"

#include "GameObject.h"
#include "SpriteRenderer.h"

#include <cmath>

namespace
{
    const std::wstring emptyClipName;
}

AnimationClip::AnimationClip(const std::wstring& name)
    : m_name(name)
{
}

void AnimationClip::AddKeyFrame(const KeyFrame& keyFrame)
{
    m_keyFrames.push_back(keyFrame);
}

float AnimationClip::GetLength() const
{
    float length = 0.0f;

    for (const KeyFrame& keyFrame : m_keyFrames)
    {
        const float endTime = keyFrame.startTime + keyFrame.duration;
        if (endTime > length)
        {
            length = endTime;
        }
    }

    return length;
}

float AnimationClip::FramesToSeconds(float frameCount, float frameRate)
{
    return frameRate > 0.0f ? frameCount / frameRate : 0.0f;
}

KeyFrame AnimationClip::Position(float startFrame, const std::wstring& targetName, const Vector2& startValue, const Vector2& endValue, float durationFrames, EaseType easeType)
{
    KeyFrame keyFrame;
    keyFrame.startTime = FramesToSeconds(startFrame);
    keyFrame.targetName = targetName;
    keyFrame.type = KeyFrameType::Position;
    keyFrame.startValue = startValue;
    keyFrame.endValue = endValue;
    keyFrame.duration = FramesToSeconds(durationFrames);
    keyFrame.easeType = easeType;
    return keyFrame;
}

KeyFrame AnimationClip::Rotation(float startFrame, const std::wstring& targetName, float startAngle, float endAngle, float durationFrames, EaseType easeType)
{
    KeyFrame keyFrame;
    keyFrame.startTime = FramesToSeconds(startFrame);
    keyFrame.targetName = targetName;
    keyFrame.type = KeyFrameType::Rotation;
    keyFrame.startValue = Vector2(startAngle, 0.0f);
    keyFrame.endValue = Vector2(endAngle, 0.0f);
    keyFrame.duration = FramesToSeconds(durationFrames);
    keyFrame.easeType = easeType;
    return keyFrame;
}

KeyFrame AnimationClip::Scale(float startFrame, const std::wstring& targetName, const Vector2& startScale, const Vector2& endScale, float durationFrames, EaseType easeType)
{
    KeyFrame keyFrame;
    keyFrame.startTime = FramesToSeconds(startFrame);
    keyFrame.targetName = targetName;
    keyFrame.type = KeyFrameType::Scale;
    keyFrame.startValue = startScale;
    keyFrame.endValue = endScale;
    keyFrame.duration = FramesToSeconds(durationFrames);
    keyFrame.easeType = easeType;
    return keyFrame;
}

KeyFrame AnimationClip::PositionTo(float startFrame, const std::wstring& targetName, const Vector2& endValue, float durationFrames, EaseType easeType)
{
    KeyFrame keyFrame = Position(startFrame, targetName, Vector2(0.0f, 0.0f), endValue, durationFrames, easeType);
    keyFrame.useCurrentAsStartValue = true;
    return keyFrame;
}

KeyFrame AnimationClip::RotationTo(float startFrame, const std::wstring& targetName, float endAngle, float durationFrames, EaseType easeType)
{
    KeyFrame keyFrame = Rotation(startFrame, targetName, 0.0f, endAngle, durationFrames, easeType);
    keyFrame.useCurrentAsStartValue = true;
    return keyFrame;
}

KeyFrame AnimationClip::ScaleTo(float startFrame, const std::wstring& targetName, const Vector2& endScale, float durationFrames, EaseType easeType)
{
    KeyFrame keyFrame = Scale(startFrame, targetName, Vector2(1.0f, 1.0f), endScale, durationFrames, easeType);
    keyFrame.useCurrentAsStartValue = true;
    return keyFrame;
}

KeyFrame AnimationClip::PositionBy(float startFrame, const std::wstring& targetName, const Vector2& deltaValue, float durationFrames, EaseType easeType)
{
    KeyFrame keyFrame = Position(startFrame, targetName, Vector2(0.0f, 0.0f), deltaValue, durationFrames, easeType);
    keyFrame.useCurrentAsStartValue = true;
    keyFrame.useDeltaAsEndValue = true;
    return keyFrame;
}

KeyFrame AnimationClip::RotationBy(float startFrame, const std::wstring& targetName, float deltaAngle, float durationFrames, EaseType easeType)
{
    KeyFrame keyFrame = Rotation(startFrame, targetName, 0.0f, deltaAngle, durationFrames, easeType);
    keyFrame.useCurrentAsStartValue = true;
    keyFrame.useDeltaAsEndValue = true;
    return keyFrame;
}

KeyFrame AnimationClip::ScaleBy(float startFrame, const std::wstring& targetName, const Vector2& deltaScale, float durationFrames, EaseType easeType)
{
    KeyFrame keyFrame = Scale(startFrame, targetName, Vector2(0.0f, 0.0f), deltaScale, durationFrames, easeType);
    keyFrame.useCurrentAsStartValue = true;
    keyFrame.useDeltaAsEndValue = true;
    return keyFrame;
}

KeyFrame AnimationClip::Sprite(float startFrame, const std::wstring& targetName, int frameIndex)
{
    KeyFrame keyFrame;
    keyFrame.startTime = FramesToSeconds(startFrame);
    keyFrame.targetName = targetName;
    keyFrame.type = KeyFrameType::Sprite;
    keyFrame.valueInt = frameIndex;
    return keyFrame;
}

KeyFrame AnimationClip::Active(float startFrame, const std::wstring& targetName, bool active)
{
    KeyFrame keyFrame;
    keyFrame.startTime = FramesToSeconds(startFrame);
    keyFrame.targetName = targetName;
    keyFrame.type = KeyFrameType::Active;
    keyFrame.valueInt = active ? 1 : 0;
    return keyFrame;
}

void Animator::AddClip(const AnimationClip& clip)
{
    m_clips.push_back(clip);
}

bool Animator::Play(const std::wstring& clipName, bool restart)
{
    for (size_t i = 0; i < m_clips.size(); ++i)
    {
        if (m_clips[i].GetName() != clipName)
        {
            continue;
        }

        if (m_currentClipIndex == static_cast<int>(i) && !restart)
        {
            return true;
        }

        m_currentClipIndex = static_cast<int>(i);
        m_time = 0.0f;
        ResetRuntimeState(m_clips[i]);
        return true;
    }

    return false;
}

void Animator::Stop()
{
    m_currentClipIndex = -1;
    m_time = 0.0f;
}

const std::wstring& Animator::GetCurrentClipName() const
{
    if (m_currentClipIndex < 0 || m_currentClipIndex >= static_cast<int>(m_clips.size()))
    {
        return emptyClipName;
    }

    return m_clips[m_currentClipIndex].GetName();
}

void Animator::Update(float deltaTime)
{
    if (m_currentClipIndex < 0 || m_currentClipIndex >= static_cast<int>(m_clips.size()))
    {
        return;
    }

    AnimationClip& clip = m_clips[m_currentClipIndex];
    std::vector<KeyFrame>& keyFrames = clip.GetKeyFrames();
    if (keyFrames.empty())
    {
        return;
    }

    m_time += deltaTime;

    const float clipLength = clip.GetLength();
    if (clipLength > 0.0f && m_time > clipLength)
    {
        if (clip.IsLooping())
        {
            m_time = std::fmod(m_time, clipLength);
            ResetRuntimeState(clip);
        }
        else
        {
            m_time = clipLength;
        }
    }

    for (KeyFrame& keyFrame : keyFrames)
    {
        const float endTime = keyFrame.startTime + keyFrame.duration;

        if (keyFrame.duration <= 0.0f)
        {
            // Sprite/Active 키는 즉시 이벤트입니다. startTime에 도달했을 때 한 번만 실행합니다.
            if (m_time >= keyFrame.startTime && !keyFrame.hasStarted)
            {
                keyFrame.hasStarted = true;
                InitializeKeyFrameStartValue(keyFrame);
                ApplyKeyFrame(keyFrame, 1.0f);
            }

            continue;
        }

        if (m_time < keyFrame.startTime || m_time > endTime)
        {
            continue;
        }

        if (!keyFrame.hasStarted)
        {
            keyFrame.hasStarted = true;

            if (keyFrame.useCurrentAsStartValue)
            {
                // *To 키는 시작 순간의 현재 포즈를 기준으로 보간합니다.
                GameObject* target = GetOwner() ? GetOwner()->FindChild(keyFrame.targetName) : nullptr;
                if (!target)
                {
                    continue;
                }

                const Transform& transform = target->GetAniTransform();
                if (keyFrame.type == KeyFrameType::Position)
                {
                    keyFrame.startValue = transform.position;
                }
                else if (keyFrame.type == KeyFrameType::Rotation)
                {
                    keyFrame.startValue = Vector2(transform.rotation, 0.0f);
                }
                else if (keyFrame.type == KeyFrameType::Scale)
                {
                    keyFrame.startValue = transform.scale;
                }
            }
        }

        const float t = (m_time - keyFrame.startTime) / keyFrame.duration;
        ApplyKeyFrame(keyFrame, ApplyEase(t, keyFrame.easeType));
    }
}

float Animator::ApplyEase(float t, EaseType easeType) const
{
    if (t < 0.0f)
    {
        t = 0.0f;
    }
    else if (t > 1.0f)
    {
        t = 1.0f;
    }

    switch (easeType)
    {
    case EaseType::Linear:
        return t;
    case EaseType::EaseIn:
        return t * t;
    case EaseType::EaseOut:
        return 1.0f - (1.0f - t) * (1.0f - t);
    case EaseType::EaseInOut:
        return t * t * (3.0f - 2.0f * t);
    default:
        return t;
    }
}

void Animator::ResetRuntimeState(AnimationClip& clip)
{
    for (KeyFrame& keyFrame : clip.GetKeyFrames())
    {
        keyFrame.hasStarted = false;
    }
}

void Animator::InitializeKeyFrameStartValue(KeyFrame& keyFrame)
{
    if (!keyFrame.useCurrentAsStartValue)
    {
        return;
    }

    GameObject* target = GetOwner() ? GetOwner()->FindChild(keyFrame.targetName) : nullptr;
    if (!target)
    {
        return;
    }

    const Transform& transform = target->GetAniTransform();
    if (keyFrame.type == KeyFrameType::Position)
    {
        keyFrame.startValue = transform.position;
    }
    else if (keyFrame.type == KeyFrameType::Rotation)
    {
        keyFrame.startValue = Vector2(transform.rotation, 0.0f);
    }
    else if (keyFrame.type == KeyFrameType::Scale)
    {
        keyFrame.startValue = transform.scale;
    }
}

void Animator::ApplyKeyFrame(KeyFrame& keyFrame, float t)
{
    GameObject* target = GetOwner() ? GetOwner()->FindChild(keyFrame.targetName) : nullptr;
    if (!target)
    {
        return;
    }

    Transform& transform = target->GetAniTransform();

    switch (keyFrame.type)
    {
    case KeyFrameType::Position:
        transform.position = keyFrame.useDeltaAsEndValue
            ? keyFrame.startValue + keyFrame.endValue * t
            : keyFrame.startValue + (keyFrame.endValue - keyFrame.startValue) * t;
        break;
    case KeyFrameType::Rotation:
        transform.rotation = keyFrame.useDeltaAsEndValue
            ? keyFrame.startValue.x + keyFrame.endValue.x * t
            : keyFrame.startValue.x + (keyFrame.endValue.x - keyFrame.startValue.x) * t;
        break;
    case KeyFrameType::Scale:
        transform.scale = keyFrame.useDeltaAsEndValue
            ? keyFrame.startValue + keyFrame.endValue * t
            : keyFrame.startValue + (keyFrame.endValue - keyFrame.startValue) * t;
        break;
    case KeyFrameType::Sprite:
        if (SpriteRenderer* renderer = target->GetComponent<SpriteRenderer>())
        {
            renderer->SetFrame(keyFrame.valueInt);
        }
        break;
    case KeyFrameType::Active:
        target->SetActive(keyFrame.valueInt == 1);
        break;
    }
}
