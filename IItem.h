#pragma once
#include "global.h"
class GObject;
class Sprite;

class IItem
{
	virtual IItem* Init(int item_code, tstring name) = 0;	
	virtual void OnHold(GObject* owner) = 0;					//아이템을 들고있을 때 동작
	virtual int get_item_code() = 0;
};

