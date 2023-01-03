#pragma once
#include "global.h"
#include "IItem.h"
#include "IUsable.h"
class Equip : public IUsable, public IItem
{
private:
	Equip()
	: item_code_(0) {};
	~Equip() {};
	int item_code_ = 0;
	tstring name_;

public:
	virtual IItem* Init(int item_code, tstring name) override;
	virtual void OnHold(GObject* owner) override;
	virtual void Use(GObject* obj) override;
	virtual int get_item_code() override;


	friend class ItemDb;
};

