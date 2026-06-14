#pragma once

#include "Animation.h"

class Animator;
class SpriteRig;

namespace WizardRaid
{
    class CoffiaCharacterFactory
    {
    public:
        static void LoadResources();
        static void ConfigureRig(SpriteRig& rig);
        static void ConfigureAnimator(Animator& animator);

        static AnimationClip CreateIdleClip();
        static AnimationClip Greeting_SmilingEyes_Clip();
        static AnimationClip ChinRest_Clip();
        static AnimationClip CreateGreeting_Clip();



        // ²Ù¹÷ ÀÎ»ç
		static AnimationClip PoliteGreeting_Clip();
    };
}
