#pragma once
#include "global.h"
#include "RealObject.h" 
class Vender : public RealObject
{
public:
	void Init();
	void CreateInteractor();
	// RealObject을(를) 통해 상속됨
	virtual void Update() override;
	void OnInteract(const GObject* obj) override;
};

