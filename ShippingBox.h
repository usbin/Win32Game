#pragma once
#include "global.h"
#include "RealObject.h"
class ShippingBox : public RealObject
{
public:
	void Init();
	virtual void CreateInteractor() override;
	// RealObject��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void OnInteract(const GObject* req_obj) override;
};

