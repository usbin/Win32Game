#pragma once
#include "global.h"
#include "IItem.h"
#include "IUsable.h"
class Equip : public IUsable, public IItem
{
private:
	Equip()
	: item_code_(0) {};
	~Equip();
	int item_code_ = 0;
	tstring name_;
	ItemSprite* sprite_ = nullptr;

public:
	virtual IItem* Init(int item_code, tstring name) override;
	virtual void OnHold(RealObject* owner) const override;
	virtual void Use(RealObject* obj) override;
	virtual int get_item_code() const override;
	virtual ItemSprite* get_sprite() const override { return sprite_; };


	friend class ItemDb;

};

