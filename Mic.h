#pragma once
#include "global.h"
#include "IItem.h"
class Mic : public IItem
{
private:
	Mic() {};
	~Mic() {};

	int item_code_ = 0;
	tstring name_;

public:

	// IItem을(를) 통해 상속됨
	virtual IItem* Init(int item_code, tstring name) override;
	virtual void OnHold(GObject* owner) override;
	virtual int get_item_code() override;

	friend class ItemDb;
};

