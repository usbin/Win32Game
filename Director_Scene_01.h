#pragma once
#include "global.h"
#include "RealObject.h"
class Director_Scene_01 : public RealObject
{
public:
	Director_Scene_01();
	~Director_Scene_01();

	// RealObject을(를) 통해 상속됨
	virtual void Update() override;
};

