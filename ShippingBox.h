#pragma once
#include "global.h"
#include "RealObject.h"
class ShippingBox : public RealObject
{
public:
	void Init();
	virtual void CreateInteractor() override;
	// RealObject을(를) 통해 상속됨
	virtual void Update() override;
	virtual void OnInteract(const GObject* req_obj) override;
};

