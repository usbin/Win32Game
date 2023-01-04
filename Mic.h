#pragma once
#include "global.h"
#include "IItem.h"
class Mic : public IItem
{
private:
	Mic() {};
	~Mic();

	int item_code_ = 0;
	tstring name_;
	bool is_dead_ = false;
	ItemSprite* sprite_ = nullptr;
public:

	// IItem을(를) 통해 상속됨
	virtual IItem* Init(int item_code, tstring name) override;
	virtual void OnHold(RealObject* owner) const override;
	virtual int get_item_code() const override;
	virtual ItemSprite* get_sprite() const override { return sprite_; };

	friend class ItemDb;
};

