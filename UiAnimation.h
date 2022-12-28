#pragma once
#include "Animation.h"
class UiAnimation : public Animation
{
public:
	UiAnimation();
	~UiAnimation();
	

	// Animation을(를) 통해 상속됨
	virtual void Render(ID3D11Device* p_d3d_device) override;

};

