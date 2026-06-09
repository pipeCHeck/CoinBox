#include "SpriteRig.h"

#include "GameObject.h"
#include "SpriteRenderer.h"

#include <memory>

GameObject* SpriteRig::AddNode(
    const std::wstring& parentName,
    const std::wstring& name,
    const Vector2& position,
    const Vector2& pivot,
    const SpriteSheetInfo& sheet,
    bool visible,
    int renderOrder,
    const std::wstring& textureKey)
{
    GameObject* owner = GetOwner();
    if (!owner || name.empty())
    {
        return nullptr;
    }

    if (GameObject* existing = FindNode(name))
    {
        // 애니메이션 클립이 이름으로 노드를 찾기 때문에, 리그 안의 노드 이름은 고유해야 합니다.
        return existing;
    }

    GameObject* parent = ResolveParent(parentName);
    if (!parent)
    {
        return nullptr;
    }

    auto node = std::make_unique<GameObject>();
    node->SetName(name);
    node->GetTransform().position = position;

    if (visible)
    {
        // 여러 노드가 같은 텍스처를 공유할 수 있습니다.
        // textureKey를 비우면 노드 이름을 ResourceManager 키로 사용합니다.
        const std::wstring& resolvedTextureKey = textureKey.empty() ? name : textureKey;
        SpriteRenderer* renderer = node->AddComponent<SpriteRenderer>(resolvedTextureKey);
        renderer->SetPivot(pivot);
        renderer->SetSpriteSheet(sheet.columns, sheet.rows, sheet.frameCount);
        renderer->SetFrame(sheet.frame);
        renderer->SetRenderOrder(renderOrder);
    }

    GameObject* added = parent->AddChild(std::move(node));
    m_nodes[name] = added;
    return added;
}

GameObject* SpriteRig::FindNode(const std::wstring& name) const
{
    const auto found = m_nodes.find(name);
    if (found != m_nodes.end())
    {
        return found->second;
    }

    GameObject* owner = GetOwner();
    return owner ? owner->FindChild(name) : nullptr;
}

SpriteRenderer* SpriteRig::FindRenderer(const std::wstring& name) const
{
    GameObject* node = FindNode(name);
    return node ? node->GetComponent<SpriteRenderer>() : nullptr;
}

GameObject* SpriteRig::ResolveParent(const std::wstring& parentName) const
{
    GameObject* owner = GetOwner();
    if (!owner)
    {
        return nullptr;
    }

    if (parentName.empty() || parentName == owner->GetName())
    {
        // parentName이 비어 있으면 루트 바로 아래에 붙는 헬퍼/Null 노드로 봅니다.
        return owner;
    }

    return FindNode(parentName);
}
