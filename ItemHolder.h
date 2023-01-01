#pragma once
#include "global.h"

//아이템을 눈에 보이게 들고있는 파츠
class ItemHolder
{
public:
	ItemHolder() {};
	~ItemHolder() {};


public:
	void Update();
	void Render(ID3D11Device* p_d3d_device);
};

