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
	// IItem��(��) ���� ��ӵ�
	virtual IItem* Init(int item_code, tstring name) override;
	virtual void OnHold(GObject* owner) override;
	virtual int get_item_code() override;

	// IUsable��(��) ���� ��ӵ�
	virtual void Use(GObject* obj) override;

	friend class ItemDb;
};

