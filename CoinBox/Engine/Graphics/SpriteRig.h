#pragma once

#include "Component.h"
#include "Vector2.h"

#include <string>
#include <unordered_map>

class SpriteRenderer;

struct SpriteSheetInfo
{
    // 스프라이트시트의 가로/세로 칸 수입니다. 일반 단일 이미지는 기본값 그대로 두면 됩니다.
    int columns = 1;
    int rows = 1;
    int frameCount = 1;
    // 시트 안에서 처음 보여줄 프레임 인덱스입니다.
    int frame = 0;
};

// 여러 스프라이트 파츠로 이루어진 캐릭터/소품의 자식 GameObject 계층을 만듭니다.
// 각 노드는 이름을 가지므로 애니메이션 클립에서 targetName으로 찾아 움직일 수 있습니다.
class SpriteRig : public Component
{
public:
    // parentName 아래에 이름 있는 자식 노드를 만들고, 필요하면 SpriteRenderer까지 붙입니다.
    //
    // parentName  : 빈 문자열이면 이 SpriteRig가 붙은 오브젝트 바로 아래에 붙입니다.
    // name        : 새 노드 이름입니다. 애니메이션은 이 이름을 targetName으로 사용합니다.
    // position    : 부모 노드 기준 로컬 위치입니다. 이 위치가 파츠의 회전 중심이 됩니다.
    // pivot       : 이미지 중심에서 실제 피벗까지의 픽셀 오프셋입니다.
    // sheet       : 스프라이트시트 칸 수와 초기 프레임 정보입니다.
    // visible     : false면 렌더러 없이 Transform만 있는 그룹용 노드를 만듭니다.
    // renderOrder : 낮을수록 먼저 그리고, 높을수록 앞에 보입니다.
    // textureKey  : ResourceManager에 등록된 텍스처 키입니다. 비우면 name을 그대로 씁니다.
    GameObject* AddNode(
        const std::wstring& parentName,
        const std::wstring& name,
        const Vector2& position,
        const Vector2& pivot = Vector2(0.0f, 0.0f),
        const SpriteSheetInfo& sheet = SpriteSheetInfo(),
        bool visible = true,
        int renderOrder = 0,
        const std::wstring& textureKey = L"");

    GameObject* FindNode(const std::wstring& name) const;
    SpriteRenderer* FindRenderer(const std::wstring& name) const;

private:
    GameObject* ResolveParent(const std::wstring& parentName) const;

    std::unordered_map<std::wstring, GameObject*> m_nodes;
};
