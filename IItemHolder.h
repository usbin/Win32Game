#pragma once
#include "global.h"
//�������� ���� ���̰� ����ִ� ����
class IItemHolder
{
public:
	virtual void Update()=0;
	virtual void Render(ID3D11Device* p_d3d_device)=0;

};

