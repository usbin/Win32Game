#pragma once
#include "global.h"
#include "ControlComponent.h"
class PlayerControlComponent : public ControlComponent
{
	// ControlComponent을(를) 통해 상속됨
	virtual void Update(RealObject* obj) override;
};

