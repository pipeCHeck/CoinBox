#pragma once
#include "Scene.h"

namespace WizardRaid
{
	class TitleScene : public ForegroundScene
	{
	protected:
		void OnInit() override;
		void OnStart() override;
	};
}

