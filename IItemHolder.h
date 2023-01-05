#pragma once
#include "global.h"
class IItem;
//아이템을 눈에 보이게 들고있는 파츠
class IItemHolder
{
public:
	virtual ~IItemHolder() = 0 {};
	virtual void Update()=0;
	virtual void Render(ID3D11Device* p_d3d_device)=0;
	virtual void SetItem(const IItem* item) = 0;
	virtual void set_owner(RealObject* owner) = 0;
	virtual RealObject* get_owner() = 0;
	virtual const IItem* get_item() = 0;
	virtual void set_hold_offset(Vector2 offset) = 0;
	virtual Vector2 get_hold_offset() = 0;
	virtual void set_hold_scale(Vector2 scale) = 0;
	virtual Vector2 get_hold_scale() = 0;
};

