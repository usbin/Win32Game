#pragma once
#include "global.h"
#include "ControlComponent.h"
class PlayerControlComponent : public ControlComponent
{
	// ControlComponent��(��) ���� ��ӵ�
	virtual void Update(RealObject* obj) override;
};

