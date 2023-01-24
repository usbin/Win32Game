#pragma once
#include "global.h"
#include "RealObject.h"
class FarmhouseDoor : public RealObject
{

public:
	~FarmhouseDoor();
	void Init();
	void CreateInteractor();
	// RealObject을(를) 통해 상속됨
	virtual void Update() override;
	virtual void OnInteract(const GObject* gobj) override;
};

