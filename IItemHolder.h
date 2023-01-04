#pragma once
#include "global.h"
class IItem;
//�������� ���� ���̰� ����ִ� ����
class IItemHolder
{
public:
	virtual ~IItemHolder() = 0 {};
	virtual void Update()=0;
	virtual void Render(ID3D11Device* p_d3d_device)=0;
	virtual void SetItem(const IItem* item) = 0;
	virtual void set_owner(RealObject* owner) = 0;

};

