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

};

