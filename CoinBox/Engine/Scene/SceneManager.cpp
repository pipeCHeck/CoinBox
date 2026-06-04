#include "SceneManager.h"

void SceneManager::Clear()
{
    m_currentScene = nullptr;
    m_foregroundScenes.clear();
    m_backgroundScene.reset();
}

void SceneManager::SetBackgroundScene(std::unique_ptr<BackgroundScene> scene)
{
    m_backgroundScene = std::move(scene);
}

ForegroundScene* SceneManager::AddForegroundScene(
    const std::wstring& name,
    std::unique_ptr<ForegroundScene> scene)
{
    ForegroundScene* rawScene = scene.get();
    m_foregroundScenes[name] = std::move(scene);
    return rawScene;
}

bool SceneManager::SetCurrentScene(const std::wstring& name)
{
    const auto foundScene = m_foregroundScenes.find(name);
    if (foundScene == m_foregroundScenes.end())
    {
        return false;
    }

    // 현재 씬을 바꿀 때 Init을 호출해서, 첫 Update 전 준비를 끝냅니다.
    m_currentScene = foundScene->second.get();
    m_currentScene->Init();
    return true;
}

// 백그라운드 씬 업데이트
void SceneManager::UpdateBackground(float deltaSeconds)
{
    if (m_backgroundScene)
    {
        m_backgroundScene->Update(deltaSeconds);
    }
}

void SceneManager::UpdateCurrent(float deltaSeconds)
{
    if (m_currentScene)
    {
        m_currentScene->Update(deltaSeconds);
    }
}

void SceneManager::RenderCurrent(ID2D1DeviceContext* d2dContext)
{
    if (m_currentScene)
    {
        m_currentScene->Render(d2dContext);
    }
}
