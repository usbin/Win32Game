#pragma once
#include "global.h"

//�������� ���� ���̰� ����ִ� ����
class ItemHolder
{
public:
	ItemHolder() {};
	~ItemHolder() {};


public:
	void Update();
	void Render(ID3D11Device* p_d3d_device);
};

