#pragma once
#include "global.h"
#include "RealObject.h"
class Director_Scene_Farm : public RealObject
{
public:
	Director_Scene_Farm();
	~Director_Scene_Farm();

	// RealObject을(를) 통해 상속됨
	virtual void Update() override;
};

