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
	Vector2 scale_ = Vector2{};

public:
	IItem* Init(int item_code, tstring name);
	virtual void OnHold(RealObject* owner) const override;
	virtual void Use(RealObject* obj) const override;
	virtual int get_item_code() const override;
	virtual ItemSprite* get_sprite() const override { return sprite_; };


	friend class ItemDb;

	// IItem을(를) 통해 상속됨
	virtual void UpdateOnHolder(IItemHolder* holder) const override;


	// IItem을(를) 통해 상속됨
	virtual void RenderOnHolder(IItemHolder* holder, ID3D11Device* p_d3d_device) const override;




	// IItem을(를) 통해 상속됨
	virtual void set_scale(Vector2 scale) override { scale_ = scale; };
	virtual Vector2 get_scale() const override { return scale_; };
};

