#pragma once
#include "global.h"
#include "IItem.h"
#include "IUsable.h"
class Crop : public IUsable, public IItem
{
private:
	Crop() {};
	~Crop();

	int item_code_ = 0;
	tstring name_;
	ItemSprite* sprite_ = nullptr;

public:
	IItem* Init(int item_code, tstring name);
	virtual void OnHold(RealObject* owner) const override;
	virtual void Use(RealObject* obj) override;
	virtual int get_item_code() const override;
	virtual ItemSprite* get_sprite() const override { return sprite_; };


	friend class ItemDb;

	// IItem을(를) 통해 상속됨
};

