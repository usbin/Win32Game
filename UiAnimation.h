#pragma once
#include "Animation.h"
class UiAnimation : public Animation
{
public:
	UiAnimation();
	~UiAnimation();
	

	// Animation��(��) ���� ��ӵ�
	virtual void Render(ID3D11Device* p_d3d_device) override;

};

