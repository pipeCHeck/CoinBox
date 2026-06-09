#pragma once

#include "GameObject.h"

#include <memory>
#include <vector>

// Scene은 GameObject들을 담는 공간입니다.
// Init / Update / Render를 돌면서 자기 오브젝트들의 컴포넌트까지 호출합니다.
class Scene
{
public:
    Scene() = default;
    virtual ~Scene() = default;

    Scene(const Scene&) = delete;
    Scene& operator=(const Scene&) = delete;

    // SceneManager나 엔진 루프가 호출합니다.
    void Init();
    void Start();
    void Update(float deltaTime);
    void Render(ID2D1DeviceContext* d2dContext);

    // 씬에 오브젝트를 추가합니다. 씬이 unique_ptr 소유권을 가져갑니다.
    GameObject* AddObject(std::unique_ptr<GameObject> object);

protected:
    // 실제 씬을 만들 때 이 함수들을 override해서 씬 전용 로직을 넣습니다.
    virtual void OnInit() {}
    virtual void OnStart() {}
    virtual void OnUpdate(float deltaTime) {}
    virtual void OnRender(ID2D1DeviceContext* d2dContext) {}

private:
    bool m_initialized = false;
    bool m_started = false;
    std::vector<std::unique_ptr<GameObject>> m_objects;
};

// 백그라운드 씬은 데이터 관리용으로 두는 씬입니다.
// 기본적으로 Render는 비워두고, 필요하면 OnUpdate에서 데이터만 갱신합니다.
class BackgroundScene : public Scene
{
protected:
    void OnRender(ID2D1DeviceContext* d2dContext) override {}
};

// 포그라운드 씬은 실제 게임 화면을 담당하는 씬입니다.
// 여러 개 만들 수 있지만, SceneManager가 현재 씬으로 고른 하나만 Update/Render됩니다.
class ForegroundScene : public Scene
{
};
