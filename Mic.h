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
	Vector2 scale_{};
public:

	// IItem��(��) ���� ��ӵ�
	virtual IItem* Init(int item_code, tstring name) override;
	virtual void OnHold(RealObject* owner) const override;
	virtual int get_item_code() const override;
	virtual ItemSprite* get_sprite() const override { return sprite_; };

	friend class ItemDb;


	// IItem��(��) ���� ��ӵ�
	virtual void UpdateOnHolder(IItemHolder* holder) const override;


	// IItem��(��) ���� ��ӵ�
	virtual void RenderOnHolder(IItemHolder* holder, ID3D11Device* p_d3d_device) const override;



	// IItem��(��) ���� ��ӵ�
	virtual void set_scale(Vector2 scale) override { scale_ = scale; };
	virtual Vector2 get_scale() const override { return scale_; };

};

