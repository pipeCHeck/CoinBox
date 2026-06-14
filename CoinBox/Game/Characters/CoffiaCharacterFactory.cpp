#include "CoffiaCharacterFactory.h"

#include "GameObject.h"
#include "ResourceManager.h"
#include "SpriteRig.h"

namespace WizardRaid
{
    void CoffiaCharacterFactory::LoadResources()
    {
        ResourceManager::LoadTexture(L"ArmL", L"Images/Coffia/ArmL.png");
        ResourceManager::LoadTexture(L"Body", L"Images/Coffia/Body.png");
        ResourceManager::LoadTexture(L"Body_ArmL", L"Images/Coffia/Body_ArmL.png");
        ResourceManager::LoadTexture(L"Body_ArmR", L"Images/Coffia/Body_ArmR.png");
        ResourceManager::LoadTexture(L"Effects", L"Images/Coffia/Effects.png");
        ResourceManager::LoadTexture(L"EyeL_Brow", L"Images/Coffia/EyeL_Brow.png");
        ResourceManager::LoadTexture(L"EyeL_Lid", L"Images/Coffia/EyeL_Lid.png");
        ResourceManager::LoadTexture(L"EyeL_Pupil", L"Images/Coffia/EyeL_Pupil.png");
        ResourceManager::LoadTexture(L"EyeL_White", L"Images/Coffia/EyeL_White.png");
        ResourceManager::LoadTexture(L"EyeR_Brow", L"Images/Coffia/EyeR_Brow.png");
        ResourceManager::LoadTexture(L"EyeR_Lid", L"Images/Coffia/EyeR_Lid.png");
        ResourceManager::LoadTexture(L"EyeR_Pupil", L"Images/Coffia/EyeR_Pupil.png");
        ResourceManager::LoadTexture(L"EyeR_White", L"Images/Coffia/EyeR_White.png");
        ResourceManager::LoadTexture(L"Face", L"Images/Coffia/Face.png");
        ResourceManager::LoadTexture(L"HairB", L"Images/Coffia/HairB.png");
        ResourceManager::LoadTexture(L"HairBL", L"Images/Coffia/HairB.png");
        ResourceManager::LoadTexture(L"HairBR", L"Images/Coffia/HairB.png");
        ResourceManager::LoadTexture(L"HairB_Head", L"Images/Coffia/HairB_Head.png");
        ResourceManager::LoadTexture(L"HairB_HeadL", L"Images/Coffia/HairB_Head.png");
        ResourceManager::LoadTexture(L"HairB_HeadR", L"Images/Coffia/HairB_Head.png");
        ResourceManager::LoadTexture(L"HairB_Head_SideTuftL", L"Images/Coffia/HairB_Head_SideTuftL.png");
        ResourceManager::LoadTexture(L"HairB_Head_SideTuftR", L"Images/Coffia/HairB_Head_SideTuftR.png");
        ResourceManager::LoadTexture(L"HairF", L"Images/Coffia/HairF.png");
        ResourceManager::LoadTexture(L"HairF_Bang", L"Images/Coffia/HairF_Bang.png");
        ResourceManager::LoadTexture(L"HairF_SideL", L"Images/Coffia/HairF_SideL.png");
        ResourceManager::LoadTexture(L"HairF_SideR", L"Images/Coffia/HairF_SideR.png");
        ResourceManager::LoadTexture(L"HairSideL_1", L"Images/Coffia/HairSideL_1.png");
        ResourceManager::LoadTexture(L"HairSideL_2", L"Images/Coffia/HairSideL_2.png");
        ResourceManager::LoadTexture(L"HairSideR_1", L"Images/Coffia/HairSideR_1.png");
        ResourceManager::LoadTexture(L"HairSideR_2", L"Images/Coffia/HairSideR_2.png");
        ResourceManager::LoadTexture(L"Hair_AhogeL", L"Images/Coffia/Hair_AhogeL.png");
        ResourceManager::LoadTexture(L"Hair_AhogeR", L"Images/Coffia/Hair_AhogeR.png");
        ResourceManager::LoadTexture(L"HandL", L"Images/Coffia/HandL.png");
        ResourceManager::LoadTexture(L"Mouth", L"Images/Coffia/Mouth.png");
        ResourceManager::LoadTexture(L"Nose", L"Images/Coffia/Nose.png");
    }

    void CoffiaCharacterFactory::ConfigureRig(SpriteRig& rig)
    {
        // 이 함수는 엔진 기능이 아니라 Coffia 캐릭터 데이터입니다.
        // AddNode 한 줄은 부모, 노드 이름, 로컬 위치, 피벗, 시트 정보, 표시 여부, 렌더 순서를 정의합니다.
        // "Null_*" 노드는 렌더러 없이 Transform만 가지는 그룹 노드입니다. 얼굴/머리/눈 묶음을 같이 움직일 때 씁니다.
        rig.AddNode(L"", L"Null_All", Vector2(0.0f, 0.0f), Vector2(), SpriteSheetInfo(), false)
            ->GetTransform().scale = Vector2(0.8f, 0.8f);

        // 몸통 계층입니다. renderOrder가 음수인 파츠는 얼굴보다 뒤에 그려집니다.
        rig.AddNode(L"Null_All", L"Body", Vector2(0.0f, 220.0f), Vector2(0.0f, 180.0f), SpriteSheetInfo(), true, -70);
        rig.AddNode(L"Body", L"Body_ArmL", Vector2(-60.0f, -298.0f), Vector2(117.0f, -158.0f), SpriteSheetInfo(), true, -80);
        rig.AddNode(L"Body", L"Body_ArmR", Vector2(60.0f, -298.0f), Vector2(-107.0f, -158.0f), SpriteSheetInfo(), true, -80);
        rig.AddNode(L"Body", L"Face", Vector2(2.0f, -362.0f), Vector2(0.0f, 140.0f), SpriteSheetInfo(), true, 0);

        rig.AddNode(L"Face", L"Nose", Vector2(0.0f, -70.0f), Vector2(), SpriteSheetInfo(), true, 20);
        rig.AddNode(L"Nose", L"Mouth", Vector2(0.0f, 33.0f), Vector2(), SpriteSheetInfo{ 9, 1, 9, 2 }, true, 30);

        // 눈 파츠는 Null 노드를 한 번 거쳐 붙여서, 나중에 눈 전체를 묶어서 움직일 수 있게 합니다.
        rig.AddNode(L"Nose", L"Null_EyeL", Vector2(-80.0f, -20.0f), Vector2(), SpriteSheetInfo(), false);
        rig.AddNode(L"Nose", L"Null_EyeR", Vector2(80.0f, -20.0f), Vector2(), SpriteSheetInfo(), false);
        rig.AddNode(L"Null_EyeL", L"EyeL_White", Vector2(0.0f, 0.0f), Vector2(), SpriteSheetInfo(), true, 25);
        rig.AddNode(L"EyeL_White", L"EyeL_Pupil", Vector2(12.0f, -2.0f), Vector2(), SpriteSheetInfo{ 1, 2, 2, 1 }, true, 26);
        rig.AddNode(L"Null_EyeL", L"EyeL_Lid", Vector2(-2.0f, -24.0f), Vector2(), SpriteSheetInfo{ 1, 2, 2, 1 }, true, 27);
        rig.AddNode(L"Null_EyeL", L"EyeL_Brow", Vector2(3.0f, -70.0f), Vector2(), SpriteSheetInfo(), true, 28);
        rig.AddNode(L"Null_EyeR", L"EyeR_White", Vector2(0.0f, 0.0f), Vector2(), SpriteSheetInfo(), true, 25);
        rig.AddNode(L"EyeR_White", L"EyeR_Pupil", Vector2(-12.0f, -2.0f), Vector2(), SpriteSheetInfo{ 1, 2, 2, 1 }, true, 26);
        rig.AddNode(L"Null_EyeR", L"EyeR_Lid", Vector2(2.0f, -24.0f), Vector2(), SpriteSheetInfo{ 1, 2, 2, 1 }, true, 27);
        rig.AddNode(L"Null_EyeR", L"EyeR_Brow", Vector2(-3.0f, -70.0f), Vector2(), SpriteSheetInfo(), true, 28);

        // HairB*는 뒷머리라 얼굴 뒤에 그립니다.
        // HairF*/HairSide*/Ahoge*는 양수 renderOrder를 써서 얼굴 위에 그립니다.
        rig.AddNode(L"Face", L"Null_Hair", Vector2(0.0f, -300.0f), Vector2(), SpriteSheetInfo(), false);
        rig.AddNode(L"Null_Hair", L"HairB_HeadL", Vector2(0.0f, -45.0f), Vector2(0.0f, -170.0f), SpriteSheetInfo{ 3, 2, 6, 0 }, true, -220);
        rig.AddNode(L"Null_Hair", L"HairB_HeadR", Vector2(0.0f, -45.0f), Vector2(0.0f, -170.0f), SpriteSheetInfo{ 3, 2, 6, 3 }, true, -220);
        rig.AddNode(L"Null_Hair", L"HairB_Head_SideTuftL", Vector2(-120.0f, 22.0f), Vector2(65.0f, -35.0f), SpriteSheetInfo{ 1, 3, 3, 0 }, true, -210);
        rig.AddNode(L"Null_Hair", L"HairB_Head_SideTuftR", Vector2(120.0f, 18.0f), Vector2(-62.0f, -50.0f), SpriteSheetInfo{ 1, 3, 3, 0 }, true, -210);
        rig.AddNode(L"Null_Hair", L"HairBL", Vector2(0.0f, 140.0f), Vector2(0.0f, -300.0f), SpriteSheetInfo{ 3, 2, 6, 0 }, true, -230);
        rig.AddNode(L"Null_Hair", L"HairBR", Vector2(0.0f, 140.0f), Vector2(0.0f, -300.0f), SpriteSheetInfo{ 3, 2, 6, 3 }, true, -230);
        rig.AddNode(L"Null_Hair", L"HairSideL_2", Vector2(-102.0f, 43.0f), Vector2(50.0f, -300.0f), SpriteSheetInfo(), true, 45);
        rig.AddNode(L"Null_Hair", L"HairSideR_2", Vector2(93.0f, 66.0f), Vector2(-50.0f, -300.0f), SpriteSheetInfo(), true, 45);
        rig.AddNode(L"Null_Hair", L"HairSideL_1", Vector2(-105.0f, 31.0f), Vector2(30.0f, -200.0f), SpriteSheetInfo(), true, 50);
        rig.AddNode(L"Null_Hair", L"HairSideR_1", Vector2(100.0f, 37.0f), Vector2(-30.0f, -200.0f), SpriteSheetInfo(), true, 50);
        rig.AddNode(L"Null_Hair", L"HairF_SideL", Vector2(2.0f, -13.0f), Vector2(93.0f, -135.0f), SpriteSheetInfo(), true, 60);
        rig.AddNode(L"Null_Hair", L"HairF_SideR", Vector2(2.0f, -13.0f), Vector2(-93.0f, -135.0f), SpriteSheetInfo(), true, 60);
        rig.AddNode(L"Null_Hair", L"HairF_Bang", Vector2(4.0f, -7.0f), Vector2(7.0f, -65.0f), SpriteSheetInfo(), true, 65);
        rig.AddNode(L"Null_Hair", L"HairF", Vector2(7.0f, -15.0f), Vector2(0.0f, -115.0f), SpriteSheetInfo(), true, 55);
        rig.AddNode(L"Null_Hair", L"Hair_AhogeL", Vector2(0.0f, -26.0f), Vector2(12.0f, 40.0f), SpriteSheetInfo{ 3, 1, 3, 0 }, true, 70);
        rig.AddNode(L"Null_Hair", L"Hair_AhogeR", Vector2(0.0f, -26.0f), Vector2(-42.0f, 40.0f), SpriteSheetInfo{ 3, 1, 3, 0 }, true, 70);

        rig.AddNode(L"Null_All", L"ArmL", Vector2(-175.0f, 200.0f), Vector2(-45.0f, 95.0f), SpriteSheetInfo{ 2, 1, 2, 0 }, true, 90);
        rig.AddNode(L"ArmL", L"HandL", Vector2(100.0f, -207.0f), Vector2(-12.0f, 70.0f), SpriteSheetInfo{ 2, 2, 4, 2 }, true, 80);
    }

    void CoffiaCharacterFactory::ConfigureAnimator(Animator& animator)
    {
        animator.AddClip(CreateIdleClip());
        animator.AddClip(Greeting_SmilingEyes_Clip());
        animator.AddClip(ChinRest_Clip());
        animator.AddClip(CreateGreeting_Clip());
		animator.AddClip(PoliteGreeting_Clip());
    }

    AnimationClip CoffiaCharacterFactory::CreateIdleClip()
    {
        AnimationClip clip(L"CoffiaIdle");
        clip.SetLooping(true);

        clip.AddKeyFrame(AnimationClip::Position(0.0f, L"Body", Vector2(0.0f, 0.0f), Vector2(0.0f, 6.0f), 60.0f, EaseType::EaseInOut));
        clip.AddKeyFrame(AnimationClip::Position(60.0f, L"Body", Vector2(0.0f, 6.0f), Vector2(0.0f, 0.0f), 60.0f, EaseType::EaseInOut));
        clip.AddKeyFrame(AnimationClip::Rotation(0.0f, L"HairF_Bang", 0.0f, 3.0f, 60.0f, EaseType::EaseInOut));
        clip.AddKeyFrame(AnimationClip::Rotation(60.0f, L"HairF_Bang", 3.0f, 0.0f, 60.0f, EaseType::EaseInOut));
        clip.AddKeyFrame(AnimationClip::Rotation(0.0f, L"Hair_AhogeL", -4.0f, 5.0f, 60.0f, EaseType::EaseInOut));
        clip.AddKeyFrame(AnimationClip::Rotation(60.0f, L"Hair_AhogeL", 5.0f, -4.0f, 60.0f, EaseType::EaseInOut));
        clip.AddKeyFrame(AnimationClip::Rotation(0.0f, L"Hair_AhogeR", 4.0f, -5.0f, 60.0f, EaseType::EaseInOut));
        clip.AddKeyFrame(AnimationClip::Rotation(60.0f, L"Hair_AhogeR", -5.0f, 4.0f, 60.0f, EaseType::EaseInOut));
        clip.AddKeyFrame(AnimationClip::Sprite(0.0f, L"Mouth", 2));
        clip.AddKeyFrame(AnimationClip::Sprite(112.0f, L"EyeL_Lid", 0));
        clip.AddKeyFrame(AnimationClip::Sprite(112.0f, L"EyeR_Lid", 0));
        clip.AddKeyFrame(AnimationClip::Sprite(116.0f, L"EyeL_Lid", 1));
        clip.AddKeyFrame(AnimationClip::Sprite(116.0f, L"EyeR_Lid", 1));

        return clip;
    }

    AnimationClip CoffiaCharacterFactory::Greeting_SmilingEyes_Clip() 
    {
        AnimationClip clip(L"Greeting_SmilingEyes_Clip");
        clip.SetLooping(true);

        clip.AddKeyFrame(clip.Active(0, L"ArmL", true));
        clip.AddKeyFrame(clip.RotationTo(0, L"ArmL", -135, 0, EaseType::Linear));
        clip.AddKeyFrame(clip.RotationTo(0, L"ArmL", -15, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(20, L"ArmL", -40, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(40, L"ArmL", -22.5f, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(60, L"ArmL", -33.75f, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(80, L"ArmL", -32.8377f, 10, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(110, L"ArmL", -123, 40, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.PositionTo(0, L"ArmL", Vector2(0, 0), 0, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(0, L"ArmL", Vector2(20, -17), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(20, L"ArmL", Vector2(9, 0), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(40, L"ArmL", Vector2(16.7f, -8), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(60, L"ArmL", Vector2(12.3f, 0.0f), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(80, L"ArmL", Vector2(12.7f, -0.7f), 10, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(110, L"ArmL", Vector2(15, 16.5), 40, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.Sprite(0, L"HandL", 2));
        clip.AddKeyFrame(clip.Sprite(0, L"HandL_Line", 3));
        clip.AddKeyFrame(clip.Active(0, L"HandL", true));
        clip.AddKeyFrame(clip.RotationTo(0, L"HandL", 20, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(20, L"HandL", -10, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(40, L"HandL", 5, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(60, L"HandL", -2, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(110, L"HandL", 7, 40, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.RotationTo(0, L"Body", -0.5f, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(20, L"Body", 0.3f, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(40, L"Body", 0, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(110, L"Body", -0.5f, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(140, L"Body", 0.2f, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(160, L"Body", 0, 16, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.PositionTo(0, L"Body", Vector2(0, -14), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(21, L"Body", Vector2(0, 4), 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(51, L"Body", Vector2(0, 0), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(110, L"Body", Vector2(0, 7), 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(140, L"Body", Vector2(0, -4), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(160, L"Body", Vector2(0, 0), 16, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.PositionTo(0, L"Nose", Vector2(0, -10), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(20, L"Nose", Vector2(0, 11), 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(50, L"Nose", Vector2(0, 0), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(110, L"Nose", Vector2(0, 3.5f), 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(140, L"Nose", Vector2(0, -2.5f), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(160, L"Nose", Vector2(0, 0), 16, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.RotationTo(0, L"HairF_SideL", -3, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(21, L"HairF_SideL", 1, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(51, L"HairF_SideL", 0, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(110, L"HairF_SideL", 2, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(140, L"HairF_SideL", -0.5f, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(160, L"HairF_SideL", 0, 16, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.RotationTo(0, L"HairF_SideR", 3, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(21, L"HairF_SideR", -1, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(51, L"HairF_SideR", 0, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(110, L"HairF_SideR", -2, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(140, L"HairF_SideR", 0.5f, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(160, L"HairF_SideR", 0, 16, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.RotationTo(0, L"HairF_Bang", 12, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(21, L"HairF_Bang", -5, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(51, L"HairF_Bang", 0, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(110, L"HairF_Bang", 5, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(140, L"HairF_Bang", -2, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(160, L"HairF_Bang", 0.5f, 16, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(176, L"HairF_Bang", 0, 10, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.ScaleTo(0, L"HairF", Vector2(1, 0.95f), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.ScaleTo(21, L"HairF", Vector2(1, 1.08f), 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.ScaleTo(51, L"HairF", Vector2(1, 1), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.ScaleTo(110, L"HairF", Vector2(1, 1.02f), 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.ScaleTo(140, L"HairF", Vector2(1, 0.98f), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.ScaleTo(160, L"HairF", Vector2(1, 1), 16, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.RotationTo(0, L"HairSideL_1", 2, 61, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(61, L"HairSideL_1", 0, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(120, L"HairSideL_1", 2, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(150, L"HairSideL_1", -0.5f, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(170, L"HairSideL_1", 0, 16, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.RotationTo(0, L"HairSideL_2", 2, 74, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(74, L"HairSideL_2", 0, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(130, L"HairSideL_2", 2, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(160, L"HairSideL_2", -0.5f, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(180, L"HairSideL_2", 0, 16, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.RotationTo(0, L"HairSideR_1", -2, 61, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(61, L"HairSideR_1", 0, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(120, L"HairSideR_1", -2, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(150, L"HairSideR_1", 0.5f, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(170, L"HairSideR_1", 0, 16, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.RotationTo(0, L"HairSideR_2", -1, 74, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(74, L"HairSideR_2", 0, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(130, L"HairSideR_2", -2, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(160, L"HairSideR_2", 0.5f, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(180, L"HairSideR_2", 0, 16, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.RotationTo(0, L"Body_ArmL", -3, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(20, L"Body_ArmL", 2, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(40, L"Body_ArmL", -3, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(60, L"Body_ArmL", 0.25f, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(80, L"Body_ArmL", 0.005457f, 15, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(95, L"Body_ArmL", 0.004346f, 10, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(105, L"Body_ArmL", -5, 40, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(145, L"Body_ArmL", 1, 25, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(170, L"Body_ArmL", 0.004346f, 16, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.RotationTo(0, L"Hair_AhogeL", -20, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(21, L"Hair_AhogeL", 10, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(51, L"Hair_AhogeL", 0, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(110, L"Hair_AhogeL", 6, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(140, L"Hair_AhogeL", -2, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(160, L"Hair_AhogeL", 0, 16, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.RotationTo(0, L"Hair_AhogeR", 20, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(21, L"Hair_AhogeR", -10, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(51, L"Hair_AhogeR", 0, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(110, L"Hair_AhogeR", -6, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(140, L"Hair_AhogeR", 2, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(160, L"Hair_AhogeR", 0, 16, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.RotationTo(0, L"HairB_HeadL", -2, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(21, L"HairB_HeadL", 0.5f, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(51, L"HairB_HeadL", 0, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(110, L"HairB_HeadL", 1, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(140, L"HairB_HeadL", -0.3f, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(160, L"HairB_HeadL", 0, 16, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.RotationTo(0, L"HairB_HeadR", 2, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(21, L"HairB_HeadR", 0.5f, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(51, L"HairB_HeadR", 0, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(110, L"HairB_HeadR", -1, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(140, L"HairB_HeadR", 0.3f, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(160, L"HairB_HeadR", 0, 16, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.Sprite(0, L"EyeL_Pupil", 0));
        clip.AddKeyFrame(clip.Sprite(0, L"EyeL_Lid", 0));
        clip.AddKeyFrame(clip.Sprite(0, L"EyeR_Pupil", 0));
        clip.AddKeyFrame(clip.Sprite(0, L"EyeR_Lid", 0));

        clip.AddKeyFrame(clip.PositionTo(0, L"EyeL_Lid", Vector2(0, 20.375f), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(110, L"EyeL_Lid", Vector2(0, 0), 30, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.ScaleTo(0, L"EyeL_White", Vector2(1, 0), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.ScaleTo(110, L"EyeL_White", Vector2(1, 1), 30, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.PositionTo(0, L"EyeR_Lid", Vector2(0, 20.375f), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(110, L"EyeR_Lid", Vector2(0, 0), 30, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.ScaleTo(0, L"EyeR_White", Vector2(1, 0), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.ScaleTo(110, L"EyeR_White", Vector2(1, 1), 30, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.Sprite(0, L"Mouth", 2));

        return clip;
    }

    AnimationClip CoffiaCharacterFactory::ChinRest_Clip()
    {
        AnimationClip clip(L"ChinRest_Clip");
        clip.SetLooping(true);

        clip.AddKeyFrame(clip.PositionTo(0, L"ArmL", Vector2(0, -49), 35, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(35, L"ArmL", Vector2(-47, -13), 15, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(50, L"ArmL", Vector2(-47, -15), 10, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(60, L"ArmL", Vector2(-49, -12.498f), 10, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.RotationTo(0, L"ArmL", 66, 0, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(0, L"ArmL", -5, 35, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(35, L"ArmL", 2, 15, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(50, L"ArmL", 1, 10, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(60, L"ArmL", 2, 10, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.Sprite(0, L"HandL", 0));
        clip.AddKeyFrame(clip.Sprite(0, L"HandL_Line", 1));
        clip.AddKeyFrame(clip.RotationTo(0, L"HandL", 0, 35, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(35, L"HandL", 4, 15, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(50, L"HandL", 3, 10, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(60, L"HandL", 0, 10, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.Sprite(0, L"Mouth", 1));
        clip.AddKeyFrame(clip.Sprite(50, L"Mouth", 2));
        clip.AddKeyFrame(clip.PositionTo(0, L"Mouth", Vector2(0, -6), 35, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(35, L"Mouth", Vector2(0, 0), 17, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.PositionTo(0, L"Nose", Vector2(0, -18.5f), 35, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(35, L"Nose", Vector2(0, 11), 17, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(52, L"Nose", Vector2(0, 5), 10, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(62, L"Nose", Vector2(0, 6.964f), 10, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(72, L"Nose", Vector2(0, 5.981f), 10, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.RotationTo(5, L"HairF_SideL", -3, 36.875f, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(41.875f, L"HairF_SideL", 5, 22.625f, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(64.5f, L"HairF_SideL", 2, 11, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(75.5f, L"HairF_SideL", 3, 11, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.RotationTo(5, L"HairF_SideR", 3, 36.875f, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(41.875f, L"HairF_SideR", 0, 22.625f, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(64.5f, L"HairF_SideR", 1, 11, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(75.5f, L"HairF_SideR", 0, 11, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.RotationTo(0, L"HairF_Bang", 9, 35, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(35, L"HairF_Bang", -6, 19, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(54, L"HairF_Bang", 3, 16.4453f, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(70.4453f, L"HairF_Bang", 0, 16.5547f, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.ScaleTo(0, L"HairF", Vector2(1, 0.86f), 35, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.ScaleTo(35, L"HairF", Vector2(1, 1.08f), 22.625f, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.ScaleTo(57.625f, L"HairF", Vector2(1, 1.05f), 11, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.ScaleTo(68.625f, L"HairF", Vector2(1, 1.06f), 11, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.RotationTo(5, L"HairSideL_1", -9, 39.625f, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(44.625f, L"HairSideL_1", 2, 22.625f, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(67.25f, L"HairSideL_1", -1, 11, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(78.25f, L"HairSideL_1", 1, 11, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.RotationTo(5, L"HairSideL_2", -9, 44.375f, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(49.375f, L"HairSideL_2", 2, 20.625f, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(70, L"HairSideL_2", -1, 11, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(81, L"HairSideL_2", 1, 11, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.RotationTo(5, L"HairSideR_1", 4, 39.625f, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(44.625f, L"HairSideR_1", 0, 22.625f, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(67.25f, L"HairSideR_1", 2, 11, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(78.25f, L"HairSideR_1", 0, 11, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.RotationTo(5, L"HairSideR_2", 5, 44.375f, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(49.375f, L"HairSideR_2", 0, 20.625f, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(70, L"HairSideR_2", 2, 11, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(81, L"HairSideR_2", 0, 11, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.PositionTo(35, L"Face", Vector2(0, 10), 17, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(52, L"Face", Vector2(0, 7), 10, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(62, L"Face", Vector2(0, 7.982f), 10, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.PositionTo(0, L"Body", Vector2(0, -13), 35, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(35, L"Body", Vector2(36, 42), 17, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(52, L"Body", Vector2(35, 41), 10, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(62, L"Body", Vector2(33, 43), 10, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.RotationTo(0, L"Body", 2, 35, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(35, L"Body", -7, 17, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(52, L"Body", -6.7f, 10, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(62, L"Body", -7, 10, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.RotationTo(0, L"Hair_AhogeL", -15, 35, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(35, L"Hair_AhogeL", 15, 17, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(52, L"Hair_AhogeL", 7.5f, 10, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(62, L"Hair_AhogeL", 0, 10, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.RotationTo(0, L"Hair_AhogeR", 12, 35, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(35, L"Hair_AhogeR", -12, 17, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(52, L"Hair_AhogeR", -6, 10, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(62, L"Hair_AhogeR", 0, 10, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.RotationTo(0, L"HairB_HeadL", -2, 42, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(42, L"HairB_HeadL", 0, 26, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(68, L"HairB_HeadL", -1, 13, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(81, L"HairB_HeadL", 0.3f, 12, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(93, L"HairB_HeadL", 0, 12, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.RotationTo(0, L"HairB_HeadR", 2, 42, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(42, L"HairB_HeadR", 0, 26, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(68, L"HairB_HeadR", 1, 13, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(81, L"HairB_HeadR", -0.3f, 12, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(93, L"HairB_HeadR", 0, 12, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.RotationTo(0, L"HairB_Head_SideTuftL", -4, 42, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(42, L"HairB_Head_SideTuftL", 2, 26, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(68, L"HairB_Head_SideTuftL", -0.5f, 13, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(81, L"HairB_Head_SideTuftL", 0.2f, 12, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(93, L"HairB_Head_SideTuftL", 0, 12, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.RotationTo(0, L"HairB_Head_SideTuftR", 4, 42, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(42, L"HairB_Head_SideTuftR", -2, 26, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(68, L"HairB_Head_SideTuftR", 0.5f, 13, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(81, L"HairB_Head_SideTuftR", -0.2f, 12, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(93, L"HairB_Head_SideTuftR", 0, 12, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.RotationTo(0, L"HairBL", -1, 42, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(42, L"HairBL", 3, 25.9473f, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(67.9473f, L"HairBL", 0, 12.7715f, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(80.7188f, L"HairBL", 2, 12.7714f, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(93.4902f, L"HairBL", 1.27913f, 11.5098f, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(105, L"HairBL", 1.54688f, 12, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.RotationTo(0, L"HairBR", 1, 42, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(42, L"HairBR", -1, 25.9473f, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(67.9473f, L"HairBR", 1, 12.7715f, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(80.7188f, L"HairBR", 0, 12.7714f, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(93.4902f, L"HairBR", 0.360436f, 11.5098f, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(105, L"HairBR", 0.226562f, 12, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.PositionTo(0, L"EyeL_Brow", Vector2(0, -7), 45, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(45, L"EyeL_Brow", Vector2(0, 8), 5, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(50, L"EyeL_Brow", Vector2(0, 0), 16, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.Sprite(50, L"EyeL_Pupil", 1));
        clip.AddKeyFrame(clip.Sprite(50, L"EyeL_Lid", 1));
        clip.AddKeyFrame(clip.Sprite(0, L"EyeL_Pupil", 0));
        clip.AddKeyFrame(clip.Sprite(0, L"EyeL_Lid", 0));
        clip.AddKeyFrame(clip.PositionTo(0, L"EyeL_Lid", Vector2(0, -5), 45, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(45, L"EyeL_Lid", Vector2(0, 16), 5, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(50, L"EyeL_Lid", Vector2(0, 0), 16, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.ScaleTo(0, L"EyeL_White", Vector2(1, 1.24f), 45, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.ScaleTo(45, L"EyeL_White", Vector2(1, 0.2f), 5, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.ScaleTo(50, L"EyeL_White", Vector2(1, 1.02f), 16, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.PositionTo(0, L"EyeR_Brow", Vector2(0, -7), 45, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(45, L"EyeR_Brow", Vector2(0, 8), 5, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(50, L"EyeR_Brow", Vector2(0, 0), 16, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.Sprite(50, L"EyeR_Pupil", 1));
        clip.AddKeyFrame(clip.Sprite(50, L"EyeR_Lid", 1));
        clip.AddKeyFrame(clip.Sprite(0, L"EyeR_Pupil", 0));
        clip.AddKeyFrame(clip.Sprite(0, L"EyeR_Lid", 0));
        clip.AddKeyFrame(clip.PositionTo(0, L"EyeR_Lid", Vector2(0, -5), 45, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(45, L"EyeR_Lid", Vector2(0, 16), 5, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(50, L"EyeR_Lid", Vector2(0, 0), 16, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.ScaleTo(0, L"EyeR_White", Vector2(1, 1.24f), 45, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.ScaleTo(45, L"EyeR_White", Vector2(1, 0.2f), 5, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.ScaleTo(50, L"EyeR_White", Vector2(1, 1.02f), 16, EaseType::EaseInOut));

        return clip;
    }

    AnimationClip CoffiaCharacterFactory::CreateGreeting_Clip()
    {
        AnimationClip clip(L"CoffiaGreeting");
        clip.SetLooping(true);

        clip.AddKeyFrame(AnimationClip::Sprite(0.0f, L"HandL", 2));
        clip.AddKeyFrame(AnimationClip::Sprite(0.0f, L"Mouth", 2));
        clip.AddKeyFrame(AnimationClip::Rotation(0.0f, L"ArmL", -135.0f, -15.0f, 20.0f, EaseType::EaseInOut));
        clip.AddKeyFrame(AnimationClip::Rotation(20.0f, L"ArmL", -15.0f, -40.0f, 20.0f, EaseType::EaseInOut));
        clip.AddKeyFrame(AnimationClip::Rotation(40.0f, L"ArmL", -40.0f, -22.5f, 20.0f, EaseType::EaseInOut));
        clip.AddKeyFrame(AnimationClip::Rotation(60.0f, L"ArmL", -22.5f, -33.75f, 20.0f, EaseType::EaseInOut));
        clip.AddKeyFrame(AnimationClip::Rotation(110.0f, L"ArmL", -33.75f, -123.0f, 40.0f, EaseType::EaseInOut));
        clip.AddKeyFrame(AnimationClip::Position(0.0f, L"ArmL", Vector2(0.0f, 0.0f), Vector2(20.0f, -17.0f), 20.0f, EaseType::EaseInOut));
        clip.AddKeyFrame(AnimationClip::Position(20.0f, L"ArmL", Vector2(20.0f, -17.0f), Vector2(9.0f, 0.0f), 20.0f, EaseType::EaseInOut));
        clip.AddKeyFrame(AnimationClip::Position(40.0f, L"ArmL", Vector2(9.0f, 0.0f), Vector2(16.7f, -8.0f), 20.0f, EaseType::EaseInOut));
        clip.AddKeyFrame(AnimationClip::Position(60.0f, L"ArmL", Vector2(16.7f, -8.0f), Vector2(12.3f, -0.7f), 20.0f, EaseType::EaseInOut));
        clip.AddKeyFrame(AnimationClip::Position(110.0f, L"ArmL", Vector2(12.3f, -0.7f), Vector2(15.0f, 16.5f), 40.0f, EaseType::EaseInOut));

        clip.AddKeyFrame(AnimationClip::Rotation(0.0f, L"HandL", 0.0f, 20.0f, 20.0f, EaseType::EaseInOut));
        clip.AddKeyFrame(AnimationClip::Rotation(20.0f, L"HandL", 20.0f, -10.0f, 20.0f, EaseType::EaseInOut));
        clip.AddKeyFrame(AnimationClip::Rotation(40.0f, L"HandL", -10.0f, 5.0f, 20.0f, EaseType::EaseInOut));
        clip.AddKeyFrame(AnimationClip::Rotation(60.0f, L"HandL", 5.0f, -2.0f, 20.0f, EaseType::EaseInOut));
        clip.AddKeyFrame(AnimationClip::Rotation(110.0f, L"HandL", -2.0f, 7.0f, 40.0f, EaseType::EaseInOut));

        clip.AddKeyFrame(AnimationClip::Position(0.0f, L"Body", Vector2(0.0f, 0.0f), Vector2(0.0f, -14.0f), 20.0f, EaseType::EaseInOut));
        clip.AddKeyFrame(AnimationClip::Position(20.0f, L"Body", Vector2(0.0f, -14.0f), Vector2(0.0f, 4.0f), 40.0f, EaseType::EaseInOut));
        clip.AddKeyFrame(AnimationClip::Position(60.0f, L"Body", Vector2(0.0f, 4.0f), Vector2(0.0f, 0.0f), 20.0f, EaseType::EaseInOut));
        clip.AddKeyFrame(AnimationClip::Rotation(0.0f, L"Body", 0.0f, -0.5f, 20.0f, EaseType::EaseInOut));
        clip.AddKeyFrame(AnimationClip::Rotation(20.0f, L"Body", -0.5f, 0.3f, 20.0f, EaseType::EaseInOut));
        clip.AddKeyFrame(AnimationClip::Rotation(40.0f, L"Body", 0.3f, 0.0f, 20.0f, EaseType::EaseInOut));

        clip.AddKeyFrame(AnimationClip::Rotation(0.0f, L"HairF_Bang", 12.0f, -5.0f, 40.0f, EaseType::EaseInOut));
        clip.AddKeyFrame(AnimationClip::Rotation(40.0f, L"HairF_Bang", -5.0f, 0.0f, 20.0f, EaseType::EaseInOut));
        clip.AddKeyFrame(AnimationClip::Rotation(110.0f, L"HairF_Bang", 0.0f, 5.0f, 20.0f, EaseType::EaseInOut));
        clip.AddKeyFrame(AnimationClip::Rotation(150.0f, L"HairF_Bang", 5.0f, 0.0f, 20.0f, EaseType::EaseInOut));
        clip.AddKeyFrame(AnimationClip::Rotation(0.0f, L"Hair_AhogeL", -20.0f, 10.0f, 40.0f, EaseType::EaseInOut));
        clip.AddKeyFrame(AnimationClip::Rotation(40.0f, L"Hair_AhogeL", 10.0f, 0.0f, 20.0f, EaseType::EaseInOut));
        clip.AddKeyFrame(AnimationClip::Rotation(0.0f, L"Hair_AhogeR", 20.0f, -10.0f, 40.0f, EaseType::EaseInOut));
        clip.AddKeyFrame(AnimationClip::Rotation(40.0f, L"Hair_AhogeR", -10.0f, 0.0f, 20.0f, EaseType::EaseInOut));

        clip.AddKeyFrame(AnimationClip::Sprite(0.0f, L"EyeL_Lid", 0));
        clip.AddKeyFrame(AnimationClip::Sprite(0.0f, L"EyeR_Lid", 0));
        clip.AddKeyFrame(AnimationClip::Sprite(110.0f, L"EyeL_Lid", 1));
        clip.AddKeyFrame(AnimationClip::Sprite(110.0f, L"EyeR_Lid", 1));
        clip.AddKeyFrame(AnimationClip::Sprite(150.0f, L"EyeL_Lid", 0));
        clip.AddKeyFrame(AnimationClip::Sprite(150.0f, L"EyeR_Lid", 0));

        return clip;
    }

    AnimationClip CoffiaCharacterFactory::PoliteGreeting_Clip()
    {
        AnimationClip clip(L"PoliteGreeting_Clip");
        clip.SetLooping(false);

        clip.AddKeyFrame(clip.PositionTo(15, L"Mouth", Vector2(0, -16), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(35, L"Mouth", Vector2(0, -12.1832f), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(155, L"Mouth", Vector2(0, 0), 25, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.PositionTo(0, L"Nose", Vector2(0, -15), 15, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(15, L"Nose", Vector2(0, 29), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(35, L"Nose", Vector2(0, 22.084f), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(155, L"Nose", Vector2(0, -15), 25, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(180, L"Nose", Vector2(0, 0), 25, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.PositionTo(15, L"HairF_SideL", Vector2(0, 26), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(35, L"HairF_SideL", Vector2(0, 19.7999f), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(155, L"HairF_SideL", Vector2(0, 0), 25, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.RotationTo(0, L"HairF_SideL", -1, 15, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(15, L"HairF_SideL", 3, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(35, L"HairF_SideL", 0.715281f, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(65, L"HairF_SideL", 2.31744f, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(95, L"HairF_SideL", 1.47208f, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(155, L"HairF_SideL", -1, 25, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(180, L"HairF_SideL", 0, 25, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.PositionTo(15, L"HairF_SideR", Vector2(0, 26), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(35, L"HairF_SideR", Vector2(0, 19.7999f), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(155, L"HairF_SideR", Vector2(0, 0), 25, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.RotationTo(0, L"HairF_SideR", 1, 15, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(15, L"HairF_SideR", -3, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(35, L"HairF_SideR", -0.715281f, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(65, L"HairF_SideR", -2.31744f, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(95, L"HairF_SideR", -1.47208f, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(155, L"HairF_SideR", 1, 25, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(180, L"HairF_SideR", 0, 25, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.PositionTo(15, L"HairF_SideR", Vector2(0, 26), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(35, L"HairF_SideR", Vector2(0, 19.7999f), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(155, L"HairF_SideR", Vector2(0, 0), 25, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.RotationTo(0, L"HairF_SideR", 1, 15, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(15, L"HairF_SideR", -3, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(35, L"HairF_SideR", -0.715281f, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(65, L"HairF_SideR", -2.31744f, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(95, L"HairF_SideR", -1.47208f, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(155, L"HairF_SideR", 1, 25, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(180, L"HairF_SideR", 0, 25, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.ScaleTo(0, L"HairF", Vector2(1, 0.91f), 15, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.ScaleTo(15, L"HairF", Vector2(1, 1.03f), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.ScaleTo(35, L"HairF", Vector2(1, 1.16f), 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.ScaleTo(155, L"HairF", Vector2(1, 0.91f), 25, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.ScaleTo(180, L"HairF", Vector2(1, 1), 25, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.PositionTo(15, L"HairF", Vector2(0, 46), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(35, L"HairF", Vector2(0, 12.0527f), 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(155, L"HairF", Vector2(0, 0), 25, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.PositionTo(15, L"HairSideL_1", Vector2(0, 20), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(35, L"HairSideL_1", Vector2(0, 15.23f), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(155, L"HairSideL_1", Vector2(0, 0), 25, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.RotationTo(0, L"HairSideL_1", -2, 15, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(15, L"HairSideL_1", 3, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(35, L"HairSideL_1", 0.715281f, 40, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(75, L"HairSideL_1", 2.31744f, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(105, L"HairSideL_1", 1.47208f, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(155, L"HairSideL_1", -2, 25, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(180, L"HairSideL_1", 0, 25, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.PositionTo(15, L"HairSideL_2", Vector2(0, 15), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(35, L"HairSideL_2", Vector2(0, 11.423f), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(155, L"HairSideL_2", Vector2(0, 0), 25, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.RotationTo(0, L"HairSideL_2", -2, 15, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(15, L"HairSideL_2", 3, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(35, L"HairSideL_2", 0.715281f, 50, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(85, L"HairSideL_2", 2.31744f, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(115, L"HairSideL_2", 1.47208f, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(155, L"HairSideL_2", -2, 25, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(180, L"HairSideL_2", 0, 25, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.PositionTo(15, L"HairSideR_1", Vector2(0, 12), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(35, L"HairSideR_1", Vector2(0, 9.138f), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(155, L"HairSideR_1", Vector2(0, 0), 25, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.RotationTo(0, L"HairSideR_1", 2, 15, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(15, L"HairSideR_1", -3, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(35, L"HairSideR_1", -0.715281f, 40, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(75, L"HairSideR_1", -2.31744f, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(105, L"HairSideR_1", -1.47208f, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(155, L"HairSideR_1", 2, 25, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(180, L"HairSideR_1", 0, 25, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.PositionTo(15, L"HairSideR_2", Vector2(0, 8), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(35, L"HairSideR_2", Vector2(0, 6.092f), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(155, L"HairSideR_2", Vector2(0, 0), 25, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.RotationTo(0, L"HairSideR_2", 2, 15, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(15, L"HairSideR_2", -3, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(35, L"HairSideR_2", -0.715281f, 50, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(85, L"HairSideR_2", -2.31744f, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(115, L"HairSideR_2", -1.47208f, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(155, L"HairSideR_2", 2, 25, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(180, L"HairSideR_2", 0, 25, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.PositionTo(15, L"Face", Vector2(0, 9), 50, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(155, L"Face", Vector2(0, 0), 25, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.PositionTo(0, L"Body", Vector2(0, -9), 15, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(15, L"Body", Vector2(0, 32), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(35, L"Body", Vector2(0, 24.369f), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(155, L"Body", Vector2(0, -9), 25, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(180, L"Body", Vector2(0, 0), 25, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.RotationTo(0, L"ArmR", 2, 15, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(15, L"ArmR", -15, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(35, L"ArmR", -11.4236f, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(155, L"ArmR", 2, 25, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(180, L"ArmR", 0, 25, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.RotationTo(0, L"ArmL", -2, 15, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(15, L"ArmL", 15, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(35, L"ArmL", 11.4236f, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(155, L"ArmL", -2, 25, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(180, L"ArmL", 0, 25, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.PositionTo(0, L"Hair_AhogeL", Vector2(0, 6), 15, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(15, L"Hair_AhogeL", Vector2(0, 20), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(35, L"Hair_AhogeL", Vector2(0, 14.8508f), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(155, L"Hair_AhogeL", Vector2(0, 6), 25, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(180, L"Hair_AhogeL", Vector2(0, 0), 25, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.RotationTo(0, L"Hair_AhogeL", -15, 15, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(15, L"Hair_AhogeL", 15, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(35, L"Hair_AhogeL", -8.4192f, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(65, L"Hair_AhogeL", 6.70422f, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(95, L"Hair_AhogeL", -1.47494f, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(155, L"Hair_AhogeL", -5.05399f, 25, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(180, L"Hair_AhogeL", 0, 25, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.PositionTo(0, L"Hair_AhogeR", Vector2(0, 6), 15, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(15, L"Hair_AhogeR", Vector2(0, 19), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(35, L"Hair_AhogeR", Vector2(0, 14.1083f), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(155, L"Hair_AhogeR", Vector2(0, 6), 25, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(180, L"Hair_AhogeR", Vector2(0, 0), 25, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.RotationTo(0, L"Hair_AhogeR", 6, 15, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(15, L"Hair_AhogeR", -25.3369f, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(35, L"Hair_AhogeR", -5.24262f, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(65, L"Hair_AhogeR", -19.1031f, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(95, L"Hair_AhogeR", -11.7868f, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(155, L"Hair_AhogeR", 2.02159f, 25, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(180, L"Hair_AhogeR", 0, 25, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.PositionTo(15, L"HairB_HeadL", Vector2(0.9722f, -10), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(35, L"HairB_HeadL", Vector2(0.7401f, -7.61239f), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(155, L"HairB_HeadL", Vector2(0, 0), 25, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.PositionTo(15, L"HairB_HeadR", Vector2(-1.0285f, -10), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(35, L"HairB_HeadR", Vector2(-0.7829f, -7.6124f), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(155, L"HairB_HeadR", Vector2(0, 0), 25, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.PositionTo(15, L"HairB_Head_SideTuftL", Vector2(0, -19), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(35, L"HairB_Head_SideTuftL", Vector2(0, -14.4683f), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(155, L"HairB_Head_SideTuftL", Vector2(0, 0), 25, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.RotationTo(0, L"HairB_Head_SideTuftL", -5, 15, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(15, L"HairB_Head_SideTuftL", 3, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(35, L"HairB_Head_SideTuftL", 0.441032f, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(65, L"HairB_Head_SideTuftL", 1.92776f, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(95, L"HairB_Head_SideTuftL", 1.35357f, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(155, L"HairB_Head_SideTuftL", -5, 25, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(180, L"HairB_Head_SideTuftL", 0, 25, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.PositionTo(15, L"HairB_Head_SideTuftR", Vector2(0, -20), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(35, L"HairB_Head_SideTuftR", Vector2(0, -15.2307f), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(155, L"HairB_Head_SideTuftR", Vector2(0, 0), 25, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.RotationTo(0, L"HairB_Head_SideTuftR", 5, 15, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(15, L"HairB_Head_SideTuftR", -3, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(35, L"HairB_Head_SideTuftR", -0.441032f, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(65, L"HairB_Head_SideTuftR", -1.92776f, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(95, L"HairB_Head_SideTuftR", -1.35357f, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(155, L"HairB_Head_SideTuftR", 5, 25, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(180, L"HairB_Head_SideTuftR", 0, 25, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.RotationTo(0, L"HairBL", -2, 15, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(15, L"HairBL", 3, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(35, L"HairBL", 0.715281f, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(65, L"HairBL", 2.31744f, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(95, L"HairBL", 1.47208f, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(155, L"HairBL", -2, 25, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(180, L"HairBL", 0, 25, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.RotationTo(0, L"HairBR", 2, 15, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(15, L"HairBR", -3, 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(35, L"HairBR", -0.715281f, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(65, L"HairBR", -2.31744f, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(95, L"HairBR", -1.47208f, 30, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(155, L"HairBR", 2, 25, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.RotationTo(180, L"HairBR", 0, 25, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.PositionTo(0, L"EyeL_Brow", Vector2(0, -10), 15, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(15, L"EyeL_Brow", Vector2(0, 22.5f), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(155, L"EyeL_Brow", Vector2(0, -10), 25, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(180, L"EyeL_Brow", Vector2(0, 0), 15, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.PositionTo(0, L"EyeR_Brow", Vector2(0, -10), 15, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(15, L"EyeR_Brow", Vector2(0, 22.5f), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(155, L"EyeR_Brow", Vector2(0, -10), 25, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(180, L"EyeR_Brow", Vector2(0, 0), 15, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.PositionTo(0, L"EyeL_Lid_Happy", Vector2(0, -4), 15, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(15, L"EyeL_Lid_Happy", Vector2(0, 20), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(155, L"EyeL_Lid_Happy", Vector2(0, -4), 25, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(180, L"EyeL_Lid_Happy", Vector2(0, 0), 15, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.PositionTo(0, L"EyeR_Lid_Happy", Vector2(0, -4), 15, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(15, L"EyeR_Lid_Happy", Vector2(0, 20), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(155, L"EyeR_Lid_Happy", Vector2(0, -4), 25, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(180, L"EyeR_Lid_Happy", Vector2(0, 0), 15, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.ScaleTo(0, L"EyeL_White", Vector2(1, 1.2f), 15, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.ScaleTo(15, L"EyeL_White", Vector2(0.95f, 0), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.ScaleTo(155, L"EyeL_White", Vector2(1, 1.2f), 25, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.ScaleTo(180, L"EyeL_White", Vector2(1, 1), 15, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.PositionTo(15, L"EyeL_White", Vector2(0, -2), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(155, L"EyeL_White", Vector2(0, 0), 25, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.ScaleTo(0, L"EyeR_White", Vector2(1, 1.2f), 15, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.ScaleTo(15, L"EyeR_White", Vector2(0.95f, 0), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.ScaleTo(155, L"EyeR_White", Vector2(1, 1.2f), 25, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.ScaleTo(180, L"EyeR_White", Vector2(1, 1), 15, EaseType::EaseInOut));

        clip.AddKeyFrame(clip.PositionTo(15, L"EyeR_White", Vector2(0, -2), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(155, L"EyeR_White", Vector2(0, 0), 25, EaseType::EaseInOut));

        return clip;
    }
}
