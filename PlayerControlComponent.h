#pragma once
#include "global.h"
#include "IControlComponent.h"
class PlayerControlComponent : public IControlComponent
{
public:
	// ControlComponent을(를) 통해 상속됨
	virtual void Update(RealObject* obj) override;

};

