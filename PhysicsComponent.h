#pragma once
#include "global.h"

class RealObject;
class PhysicsComponent
{
public:
	PhysicsComponent();
	~PhysicsComponent();

	virtual void FinalUpdate(RealObject* obj);
};

