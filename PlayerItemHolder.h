#pragma once
#include "global.h"
#include "IItemHolder.h"
#include "IItem.h"
class Player;
class PlayerItemHolder : public IItemHolder
{
public:
	PlayerItemHolder();
	virtual ~PlayerItemHolder() override;

private:
	//Ȧ���� ������ ������
	const IItem* item_ = nullptr;
	Player* owner_ = nullptr;
	Vector2 hold_offset_ = Vector2::Zero();
	Vector2 holder_scale_ = Vector2::Zero();
public:
	

	virtual void set_owner(RealObject* owner) override { owner_ = static_cast<Player*>(owner); };
	virtual void Update() override;
	virtual void Render(ID3D11Device* p_d3d_device) override; //������ ������
	virtual void SetItem(const IItem* item) override;
	virtual const IItem* get_item() override { return item_; };

	// IItemHolder��(��) ���� ��ӵ�
	inline virtual RealObject* get_owner() override { return owner_; };
	virtual void set_hold_offset(Vector2 offset) override { hold_offset_ = offset; };
	virtual Vector2 get_hold_offset() override { return hold_offset_; };

	// IItemHolder��(��) ���� ��ӵ�
	virtual void set_hold_scale(Vector2 scale) override { holder_scale_ = scale; };
	virtual Vector2 get_hold_scale() override { return holder_scale_; };
};

