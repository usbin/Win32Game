#pragma once
#include "global.h"
#include "RealObject.h"
class FarmhouseDoor_Exit : public RealObject
{
	// RealObject을(를) 통해 상속됨
public:
	void Init();
	virtual void CreateCollider() override;
	virtual void Update() override;

	virtual void OnCollisionEnter(Collider* collider) override;
};

