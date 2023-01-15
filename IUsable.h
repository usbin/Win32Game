#pragma once
#include "global.h"
class RealObject;
class ISprite;
class IUsable
{
public:
	virtual bool Use(RealObject* obj) const = 0;
};

