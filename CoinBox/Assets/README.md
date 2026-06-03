# Assets

게임에서 쓰는 외부 파일은 이 폴더 아래에 둡니다.

추천 구조:

```text
Assets/
  Images/
    player.png
  Audio/
    click.wav
```

코드에서는 전체 경로를 직접 쓰지 않고, `ResourceManager`에 상대 경로로 등록합니다.

```cpp
ResourceManager::LoadBitmap(L"player", L"Images/player.png");
ResourceManager::LoadAudio(L"click", L"Audio/click.wav");
```

사용할 때는 키 이름으로 가져옵니다.

```cpp
auto object = std::make_unique<GameObject>();
object->AddComponent<SpriteRenderer>(L"player");

ResourceManager::PlayAudio(L"click");
```
