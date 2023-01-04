#pragma once
#include "global.h"
class RealObject;
class ISprite;
class IUsable
{
public:
	virtual void Use(RealObject* obj) = 0;
};

