#pragma once
#include "global.h"
#include "IItem.h"
#include "IUsable.h"
class Seed : public IItem, public IUsable
{
private:
	Seed() {};
	~Seed() {};

	int item_code_;
	tstring name_;

public:
	// IItem을(를) 통해 상속됨
	virtual IItem* Init(int item_code, tstring name) override;
	virtual void OnHold(GObject* owner) override;
	virtual int get_item_code() override;

	// IUsable을(를) 통해 상속됨
	virtual void Use(GObject* obj) override;

	friend class ItemDb;
};

