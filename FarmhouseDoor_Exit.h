#pragma once
#include "global.h"
#include "RealObject.h"
class FarmhouseDoor_Exit : public RealObject
{
	// RealObject��(��) ���� ��ӵ�
public:
	void Init();
	virtual void CreateCollider() override;
	virtual void Update() override;

	virtual void OnCollisionEnter(Collider* collider) override;
};

