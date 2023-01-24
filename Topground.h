#pragma once
#include "global.h"
#include "RealObject.h"
class Topground : public RealObject
{
public:
	Topground();
	virtual void CreateRenderCmp() override;
	// RealObject을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render(ID3D11Device* p_d3d_device) override;
};

