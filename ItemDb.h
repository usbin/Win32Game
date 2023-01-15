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
	const IItem* get_item(int item_code);
};

