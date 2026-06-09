#pragma once

#include "Scene.h"

#include <memory>
#include <string>
#include <unordered_map>

// SceneManager는 엔진 안에서 씬들을 관리하는 관리자입니다.
// 백그라운드 씬은 하나만 갖고, 포그라운드 씬은 이름으로 여러 개 저장합니다.
class SceneManager
{
public:
    void Clear();

    // 데이터 관리용 백그라운드 씬을 등록합니다.
    void SetBackgroundScene(std::unique_ptr<BackgroundScene> scene);
    BackgroundScene* GetBackgroundScene() const { return m_backgroundScene.get(); }

    // 포그라운드 씬을 이름과 함께 등록합니다.
    // 사용 예: AddForegroundScene(L"Title", std::make_unique<TitleScene>());
    ForegroundScene* AddForegroundScene(
        const std::wstring& name,
        std::unique_ptr<ForegroundScene> scene);

    // 등록된 포그라운드 씬 중 현재 실행할 씬을 고릅니다.
    bool SetCurrentScene(const std::wstring& name);
    ForegroundScene* GetCurrentScene() const { return m_currentScene; }

    // 엔진 루프에서 호출됩니다.
    void UpdateBackground(float deltaTime);
    void UpdateCurrent(float deltaTime);
    void RenderCurrent(ID2D1DeviceContext* d2dContext);

private:
    std::unique_ptr<BackgroundScene> m_backgroundScene;
    std::unordered_map<std::wstring, std::unique_ptr<ForegroundScene>> m_foregroundScenes;

    // m_foregroundScenes 안의 씬을 가리키는 포인터입니다. 소유권은 unordered_map이 가집니다.
    ForegroundScene* m_currentScene = nullptr;
};
