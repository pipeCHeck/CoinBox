#pragma once

#include "Component.h"
#include "Transform.h"

#include <string>
#include <vector>

enum class KeyFrameType
{
    Position,
    Rotation,
    Scale,
    Sprite,
    Active,
};

enum class EaseType
{
    Linear,
    EaseIn,
    EaseOut,
    EaseInOut,
};

struct KeyFrame
{
    // 런타임에는 초 단위로 저장합니다. AnimationClip 헬퍼 함수들은 프레임 단위를 입력받습니다.
    float startTime = 0.0f;
    // Animator가 붙은 오브젝트 아래에서 찾을 대상 GameObject 이름입니다.
    std::wstring targetName;
    KeyFrameType type = KeyFrameType::Position;
    Vector2 startValue = Vector2(0.0f, 0.0f);
    Vector2 endValue = Vector2(0.0f, 0.0f);
    int valueInt = 0;
    float duration = 0.0f;
    EaseType easeType = EaseType::Linear;
    // *To 헬퍼에서 사용합니다. 재생 시간이 이 키에 도달했을 때 대상의 현재 값을 시작값으로 잡습니다.
    bool useCurrentAsStartValue = false;

    bool hasStarted = false;
};

class AnimationClip
{
public:
    explicit AnimationClip(const std::wstring& name = L"");

    const std::wstring& GetName() const { return m_name; }
    void SetName(const std::wstring& name) { m_name = name; }

    bool IsLooping() const { return m_looping; }
    void SetLooping(bool looping) { m_looping = looping; }

    void AddKeyFrame(const KeyFrame& keyFrame);
    std::vector<KeyFrame>& GetKeyFrames() { return m_keyFrames; }
    const std::vector<KeyFrame>& GetKeyFrames() const { return m_keyFrames; }
    float GetLength() const;

    // 아래 키프레임 생성 함수들은 초가 아니라 프레임 번호를 입력받습니다.
    // 엔진 업데이트 루프는 deltaTime을 쓰므로, 내부 저장값만 초 단위로 변환합니다.
    static float FramesToSeconds(float frameCount, float frameRate = 60.0f);

    static KeyFrame Position(float startFrame, const std::wstring& targetName, const Vector2& startValue, const Vector2& endValue, float durationFrames, EaseType easeType);
    static KeyFrame Rotation(float startFrame, const std::wstring& targetName, float startAngle, float endAngle, float durationFrames, EaseType easeType);
    static KeyFrame Scale(float startFrame, const std::wstring& targetName, const Vector2& startScale, const Vector2& endScale, float durationFrames, EaseType easeType);

    // *To 버전은 재생 중 키가 시작되는 순간의 현재 Transform 값을 시작값으로 사용합니다.
    static KeyFrame PositionTo(float startFrame, const std::wstring& targetName, const Vector2& endValue, float durationFrames, EaseType easeType);
    static KeyFrame RotationTo(float startFrame, const std::wstring& targetName, float endAngle, float durationFrames, EaseType easeType);
    static KeyFrame ScaleTo(float startFrame, const std::wstring& targetName, const Vector2& endScale, float durationFrames, EaseType easeType);

    static KeyFrame Sprite(float startFrame, const std::wstring& targetName, int frameIndex);
    static KeyFrame Active(float startFrame, const std::wstring& targetName, bool active);

private:
    std::wstring m_name;
    bool m_looping = false;
    std::vector<KeyFrame> m_keyFrames;
};

class Animator : public Component
{
public:
    void AddClip(const AnimationClip& clip);
    bool Play(const std::wstring& clipName, bool restart = true);
    void Stop();
    bool IsPlaying() const { return m_currentClipIndex >= 0; }
    const std::wstring& GetCurrentClipName() const;

    void Update(float deltaTime) override;

private:
    float ApplyEase(float t, EaseType easeType) const;
    void ResetRuntimeState(AnimationClip& clip);
    void ApplyKeyFrame(KeyFrame& keyFrame, float t);

    std::vector<AnimationClip> m_clips;
    int m_currentClipIndex = -1;
    float m_time = 0.0f;
};
