#pragma once
#include "global.h"
class Loading
{
public:
	float timer_ = 0.f;
public:
	void Update();
	void Render(ID3D11Device* p_d3d_device);
};

