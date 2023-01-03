#pragma once
#include "global.h"
//아이템을 눈에 보이게 들고있는 파츠
class IItemHolder
{
public:
	virtual void Update()=0;
	virtual void Render(ID3D11Device* p_d3d_device)=0;

};

