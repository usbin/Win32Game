#pragma once
#include "global.h"
#include "IControlComponent.h"
class PlayerControlComponent : public IControlComponent
{
public:
	// ControlComponent��(��) ���� ��ӵ�
	virtual void Update(RealObject* obj) override;

};

