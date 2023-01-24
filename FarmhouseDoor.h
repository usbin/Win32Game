#pragma once
#include "global.h"
#include "RealObject.h"
class FarmhouseDoor : public RealObject
{

public:
	~FarmhouseDoor();
	void Init();
	void CreateInteractor();
	// RealObject��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void OnInteract(const GObject* gobj) override;
};

