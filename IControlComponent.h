#pragma once
#include "global.h"
class RealObject;

class IControlComponent
{

public:
	virtual ~IControlComponent() = 0 {};
	virtual void Update(RealObject* obj) = 0;
};

