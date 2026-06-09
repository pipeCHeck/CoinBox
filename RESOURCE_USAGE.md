# 리소스 사용법

PNG 이미지와 WAV 사운드는 `CoinBox/Assets` 아래에 둡니다.

추천 폴더:

```text
CoinBox/
  Assets/
    Images/
      player.png
      coin.png
    Audio/
      click.wav
      bgm.wav
```

엔진은 기본 리소스 루트를 `Assets`로 잡습니다.

```cpp
ResourceManager::SetAssetRoot(L"Assets");
```

## PNG 이미지 등록

씬의 `OnInit()` 같은 초기화 지점에서 한 번 등록합니다.

```cpp
ResourceManager::LoadTexture(L"player", L"Images/player.png");
```

- `L"player"`: 코드에서 사용할 이름입니다.
- `L"Images/player.png"`: `Assets` 폴더 기준 상대 경로입니다.

## PNG 이미지 그리기

`SpriteRenderer` 컴포넌트를 오브젝트에 붙입니다.

```cpp
auto player = std::make_unique<GameObject>();
player->GetTransform().position = Vector2(300.0f, 200.0f);
player->GetTransform().scale = Vector2(1.0f, 1.0f);
player->AddComponent<SpriteRenderer>(L"player");
AddObject(std::move(player));
```

`SpriteRenderer`는 `ResourceManager`에서 `player` 키의 이미지를 찾아서 그립니다.

## WAV 사운드 등록

```cpp
ResourceManager::LoadAudio(L"click", L"Audio/click.wav");
ResourceManager::LoadAudio(L"bgm", L"Audio/bgm.wav");
```

## WAV 사운드 재생

```cpp
ResourceManager::PlayAudio(L"click");
```

반복 재생:

```cpp
ResourceManager::PlayAudio(L"bgm", true);
```

정지:

```cpp
ResourceManager::StopAudio();
```

현재 WAV 재생은 Win32 `PlaySoundW` 기반이라 간단한 효과음/배경음 확인용에 가깝습니다.
나중에 볼륨 조절, 여러 소리 동시 재생, 페이드 인/아웃이 필요하면 XAudio2 쪽으로 확장하는 것이 좋습니다.

## 주의점

이미지는 매 프레임 로딩하면 안 됩니다.

나쁜 방식:

```cpp
void Render(...)
{
    ResourceManager::LoadTexture(L"player", L"Images/player.png");
}
```

좋은 방식:

```cpp
void OnInit()
{
    ResourceManager::LoadTexture(L"player", L"Images/player.png");
}
```

렌더링할 때는 `SpriteRenderer`가 이미 등록된 이미지를 가져다 씁니다.
