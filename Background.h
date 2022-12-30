#pragma once
#include "global.h"
#include "RealObject.h"



class Background : public RealObject
{
public:
	Background();
	~Background();
private:
public:
	virtual void Update() override;
	virtual void Render(ID3D11Device* p_d3d_device) override;
};

