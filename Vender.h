#pragma once
#include "global.h"
#include "RealObject.h" 
class Vender : public RealObject
{
public:
	void Init();
	void CreateInteractor();
	// RealObject��(��) ���� ��ӵ�
	virtual void Update() override;
	void OnInteract(const GObject* obj) override;
};

