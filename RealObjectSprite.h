#pragma once
#include "global.h"
#include "GObjectSprite.h"
class RealObjectSprite : public GObjectSprite
{
public:
	RealObjectSprite() {};
	virtual ~RealObjectSprite() {};

	// Sprite��(��) ���� ��ӵ�

	virtual void Render(ID3D11Device* p_d3d_device) override;


};

