#pragma once
#include "global.h"
class IItem;

class ItemDb
{
public:
	SINGLETON(ItemDb);

private:
	std::map<int, IItem*> items_;

public:
	void Init();
	const IItem* GetItem(int item_code);
};

