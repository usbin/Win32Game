#pragma once
#include "global.h"
class RealObject;

class ControlComponent
{
public:
	ControlComponent();
	~ControlComponent();

	virtual void Update(RealObject* obj) = 0;
};

