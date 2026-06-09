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
        rig.AddNode(L"Null_All", L"Body", Vector2(0.0f, 220.0f), Vector2(0.0f, 180.0f), SpriteSheetInfo(), true, -100);
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

        rig.AddNode(L"Null_All", L"ArmL", Vector2(-175.0f, 200.0f), Vector2(-45.0f, 95.0f), SpriteSheetInfo{ 2, 1, 2, 0 }, true, 80);
        rig.AddNode(L"ArmL", L"HandL", Vector2(100.0f, -207.0f), Vector2(-12.0f, 70.0f), SpriteSheetInfo{ 2, 2, 4, 2 }, true, 90);
    }

    void CoffiaCharacterFactory::ConfigureAnimator(Animator& animator)
    {
        animator.AddClip(CreateIdleClip());
        animator.AddClip(Greeting_SmilingEyes_Clip());
        animator.AddClip(CreateGreetingClip());
        //animator.Play(L"Greeting_SmilingEyes_Clip");
    }

    AnimationClip CoffiaCharacterFactory::CreateIdleClip()
    {
        AnimationClip clip(L"CoffiaIdle");
        clip.SetLooping(true);

        clip.AddKeyFrame(AnimationClip::Position(0.0f, L"Body", Vector2(0.0f, 220.0f), Vector2(0.0f, 226.0f), 60.0f, EaseType::EaseInOut));
        clip.AddKeyFrame(AnimationClip::Position(60.0f, L"Body", Vector2(0.0f, 226.0f), Vector2(0.0f, 220.0f), 60.0f, EaseType::EaseInOut));
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
        clip.AddKeyFrame(clip.PositionTo(60, L"ArmL", Vector2(12.3, 0), 20, EaseType::EaseInOut));
        clip.AddKeyFrame(clip.PositionTo(80, L"ArmL", Vector2(12.7, -0.7), 10, EaseType::EaseInOut));
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

    AnimationClip CoffiaCharacterFactory::CreateGreetingClip()
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
        clip.AddKeyFrame(AnimationClip::Position(0.0f, L"ArmL", Vector2(-175.0f, 200.0f), Vector2(-155.0f, 183.0f), 20.0f, EaseType::EaseInOut));
        clip.AddKeyFrame(AnimationClip::Position(20.0f, L"ArmL", Vector2(-155.0f, 183.0f), Vector2(-166.0f, 200.0f), 20.0f, EaseType::EaseInOut));
        clip.AddKeyFrame(AnimationClip::Position(40.0f, L"ArmL", Vector2(-166.0f, 200.0f), Vector2(-158.3f, 192.0f), 20.0f, EaseType::EaseInOut));
        clip.AddKeyFrame(AnimationClip::Position(60.0f, L"ArmL", Vector2(-158.3f, 192.0f), Vector2(-162.7f, 199.3f), 20.0f, EaseType::EaseInOut));
        clip.AddKeyFrame(AnimationClip::Position(110.0f, L"ArmL", Vector2(-162.7f, 199.3f), Vector2(-160.0f, 216.5f), 40.0f, EaseType::EaseInOut));

        clip.AddKeyFrame(AnimationClip::Rotation(0.0f, L"HandL", 0.0f, 20.0f, 20.0f, EaseType::EaseInOut));
        clip.AddKeyFrame(AnimationClip::Rotation(20.0f, L"HandL", 20.0f, -10.0f, 20.0f, EaseType::EaseInOut));
        clip.AddKeyFrame(AnimationClip::Rotation(40.0f, L"HandL", -10.0f, 5.0f, 20.0f, EaseType::EaseInOut));
        clip.AddKeyFrame(AnimationClip::Rotation(60.0f, L"HandL", 5.0f, -2.0f, 20.0f, EaseType::EaseInOut));
        clip.AddKeyFrame(AnimationClip::Rotation(110.0f, L"HandL", -2.0f, 7.0f, 40.0f, EaseType::EaseInOut));

        clip.AddKeyFrame(AnimationClip::Position(0.0f, L"Body", Vector2(0.0f, 220.0f), Vector2(0.0f, 206.0f), 20.0f, EaseType::EaseInOut));
        clip.AddKeyFrame(AnimationClip::Position(20.0f, L"Body", Vector2(0.0f, 206.0f), Vector2(0.0f, 224.0f), 40.0f, EaseType::EaseInOut));
        clip.AddKeyFrame(AnimationClip::Position(60.0f, L"Body", Vector2(0.0f, 224.0f), Vector2(0.0f, 220.0f), 20.0f, EaseType::EaseInOut));
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
}
