#pragma once
#include "global.h"
#include "RealObject.h"

class InvisibleWall : public RealObject
{
public:
	InvisibleWall();
	virtual ~InvisibleWall();
private:

public:
	virtual void Update() override;
	virtual void Render(ID3D11Device* p_d3d_device) override;


};

