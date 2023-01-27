#pragma once
#include "RealObject.h"
#include "global.h"
class DayNightDarkness : public RealObject
{
private:
	float opacity_ = 0.f;
public:
	void Init();
	void Update();
	void Render(ID3D11Device* p_d3d_device);
};

