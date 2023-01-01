#pragma once
#include "global.h"
class GObject;
class Sprite;
class IUsable
{
public:
	virtual void Use(GObject* obj) = 0;
};

