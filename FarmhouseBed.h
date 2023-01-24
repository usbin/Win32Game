#pragma once
#include "global.h"
#include "RealObject.h"
class FarmhouseBed : public RealObject
{
public:
	void Init();
	virtual void CreateCollider() override;
	virtual void Update() override;

	virtual void OnCollisionEnter(Collider* collider) override;
};

