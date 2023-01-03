#pragma once
#include "global.h"
#include "IItem.h"
#include "IUsable.h"
class Crop : public IUsable, public IItem
{
private:
	Crop() {};
	~Crop() {};

	int item_code_ = 0;
	tstring name_;

public:
	IItem* Init(int item_code, tstring name);
	virtual void OnHold(GObject* owner) override;
	virtual void Use(GObject* obj) override;
	virtual int get_item_code() override;


	friend class ItemDb;
};

