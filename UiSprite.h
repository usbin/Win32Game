#pragma once
#include "global.h"
#include "Sprite.h"
class UiSprite : public Sprite
{
	// Sprite��(��) ���� ��ӵ�
	virtual void Render(ID3D11Device* p_d3d_device) override;
};

