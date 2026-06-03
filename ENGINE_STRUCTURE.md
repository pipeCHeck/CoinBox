# CoinBox Engine Structure

이 프로젝트는 앱 코드와 엔진 코드를 분리해서 관리합니다.

## App

`CoinBox/`

- `CoinBox.cpp`: Win32 진입점, 윈도우 생성, 메시지 루프
- `CoinBox.h`, `Resource.h`, `CoinBox.rc`: 앱 리소스
- `Catalog.*`: 앱 또는 게임 데이터 쪽 코드로 사용할 후보

## Engine

`CoinBox/Engine/`

- `Core/`: 오브젝트와 컴포넌트의 기본 구조
  - `Component`: 모든 컴포넌트의 부모
  - `GameObject`: 컴포넌트를 담는 오브젝트
  - `Transform`: 위치, 회전, 크기를 가진 기본 컴포넌트
- `Scene/`: 씬 구조와 씬 관리자
  - `Scene`: 오브젝트 목록을 돌리는 기본 씬
  - `SceneManager`: 백그라운드 씬과 현재 포그라운드 씬 관리
- `Input/`: 키보드/마우스 입력 상태
  - `Input::IsKey`
  - `Input::IsKeyDown`
  - `Input::IsKeyUp`
  - `Input::IsMouse`
  - `Input::GetMousePosition`
- `Graphics/`: D2D 장치, 렌더 루프, 그래픽 시스템
  - `D2DGameEngine`: 엔진 초기화, Tick, Update, Render
- `Resources/`: 외부 파일 위치와 로딩 관리
  - `ResourceManager`: PNG/WAV 파일을 키로 등록하고 가져오기

## Where To Add Things

- 새 컴포넌트: `Engine/Core` 또는 새 하위 폴더 `Engine/Components`
- 도형/이미지/글자 렌더러: `Engine/Graphics`
- 키보드/마우스/패드 입력: `Engine/Input`
- 씬 전환, 씬 스택, 로딩 씬: `Engine/Scene`
- 이미지/폰트 같은 리소스 관리: 새 폴더 `Engine/Resources`
- 충돌 처리: 새 폴더 `Engine/Physics`
- 실제 게임용 씬과 오브젝트 조립 코드: 새 폴더 `CoinBox/Game`

## Suggested Next Steps

1. `Engine/Graphics/ShapeRenderer` 만들기
2. `Engine/Graphics/SpriteRenderer` 만들기
3. `Engine/Resources/ResourceManager` 만들기
4. `Engine/Physics/BoxCollider` 만들기
5. 샘플 씬 코드를 `D2DGameEngine.cpp`에서 `CoinBox/Game` 쪽으로 분리하기
