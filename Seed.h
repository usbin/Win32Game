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
	Vector2 scale_{};
public:
	// IItem��(��) ���� ��ӵ�
	virtual IItem* Init(int item_code, tstring name);
	virtual void OnHold(RealObject* owner) const override;
	virtual int get_item_code() const override;
	virtual ItemSprite* get_sprite() const override { return sprite_; };

	// IUsable��(��) ���� ��ӵ�
	virtual void Use(RealObject* obj) const override;


	friend class ItemDb;


	// IItem��(��) ���� ��ӵ�
	virtual void UpdateOnHolder(IItemHolder* holder) const override;



	// IItem��(��) ���� ��ӵ�
	virtual void RenderOnHolder(IItemHolder* holder, ID3D11Device* p_d3d_device) const override;


	virtual void set_scale(Vector2 scale) override { scale_ = scale; };
	virtual Vector2 get_scale() const override { return scale_; };

};

