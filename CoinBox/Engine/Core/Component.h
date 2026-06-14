#pragma once

#include <d2d1_1.h>
#include "Vector2.h"

class GameObject;
struct Collision2D;

// Component는 GameObject에 붙는 기능 조각입니다.
// 예: 이동 담당 MoveComponent, 이미지 출력 SpriteRenderer, 체력 관리 HealthComponent.
class Component
{
public:
    virtual ~Component() = default;

    // 이 컴포넌트가 붙어 있는 GameObject를 얻습니다.
    // 다른 컴포넌트를 찾거나 오브젝트 상태를 확인할 때 사용합니다.
    GameObject* GetOwner() const { return m_owner; }

    // 오브젝트가 처음 준비될 때 한 번 호출됩니다.
    virtual void Init() {}

    // 
    virtual void Start() {}

    // 매 프레임 호출됩니다. deltaTime는 이전 프레임 이후 지난 시간(초)입니다.
    virtual void Update(float deltaTime) {}

    // 매 프레임 그릴 때 호출됩니다. D2D 그리기 명령은 여기서 실행합니다.
    virtual void Render(ID2D1DeviceContext* d2dContext) {}

    virtual void OnCollisionEnter2D(const Collision2D& collision) {}
    virtual void OnCollisionStay2D(const Collision2D& collision) {}
    virtual void OnCollisionExit2D(const Collision2D& collision) {}

    // 같은 GameObject 트리 안에서 렌더 순서를 정합니다. 값이 클수록 나중에 그립니다.
    virtual int GetRenderOrder() const { return 0; }

    // Screen-space UI는 카메라 행렬의 영향을 받지 않는 별도 렌더 패스에서 그립니다.
    virtual bool IsScreenSpaceUI() const { return false; }

protected:
    static float Clamp01(float value)
    {
        if (value < 0.0f)
        {
            return 0.0f;
        }

        if (value > 1.0f)
        {
            return 1.0f;
        }

        return value;
    }

    static float EaseInOut(float t)
    {
        t = Clamp01(t);
        return t * t * (3.0f - 2.0f * t);
    }

    static float Lerp(float start, float end, float t)
    {
        t = Clamp01(t);
        return start + (end - start) * t;
    }

    static Vector2 Lerp(const Vector2& start, const Vector2& end, float t)
    {
        t = Clamp01(t);
        return start + (end - start) * t;
    }

    static Vector2 SmoothFollow(const Vector2& current, const Vector2& target, float speed, float deltaTime)
    {
        return Lerp(current, target, speed * deltaTime);
    }

private:
    friend class GameObject;

    // Component는 GameObject::AddComponent로 붙이게 하고,
    // owner 설정은 GameObject만 할 수 있게 숨겨둡니다.
    void SetOwner(GameObject* owner) { m_owner = owner; }

    GameObject* m_owner = nullptr;
};
