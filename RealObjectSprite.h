#pragma once
#include "global.h"
#include "Sprite.h"
class RealObjectSprite : public Sprite
{
public:
	RealObjectSprite() {};
	virtual ~RealObjectSprite() {};

	// Sprite을(를) 통해 상속됨
	virtual void Render(ID3D11Device* p_d3d_device) override;


};

