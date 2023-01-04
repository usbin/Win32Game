#pragma once
#include "global.h"
#include "IItem.h"
#include "IUsable.h"
class Seed : public IItem, public IUsable
{
private:
	Seed() {};
	~Seed();

	int item_code_ = 0;
	tstring name_;
	ItemSprite* sprite_ = nullptr;
public:
	// IItem을(를) 통해 상속됨
	virtual IItem* Init(int item_code, tstring name) override;
	virtual void OnHold(RealObject* owner) const override;
	virtual int get_item_code() const override;
	virtual ItemSprite* get_sprite() const override { return sprite_; };

	// IUsable을(를) 통해 상속됨
	virtual void Use(RealObject* obj) override;


	friend class ItemDb;
};

