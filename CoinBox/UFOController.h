#pragma once
#include "Component.h"

namespace WizardRaid
{
    class UFOAttack;
    class UFOSuction;
    class UFODash;
    class UFOMovement;
    class UFOStats;

    class UFOController : public Component
    {
    protected:
        void Start() override;
        void Update(float deltaTime) override;
    private:
        UFOAttack* m_attack = nullptr;
        UFOSuction* m_suction = nullptr;
        UFODash* m_dash = nullptr;
        UFOMovement* m_movement = nullptr;
        UFOStats* m_stats = nullptr;
    };

}
