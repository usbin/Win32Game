#pragma once
#include "Animation.h"
class RealObjectAnimation : public Animation 
{
private:
	RENDER_LAYER layer_ = RENDER_LAYER::DEFAULT;
public:
	RealObjectAnimation();
	~RealObjectAnimation();
	// Animation을(를) 통해 상속됨
	virtual void Render(ID3D11Device* p_d3d_device) override;
	virtual void set_layer(RENDER_LAYER layer) { layer_ = layer; };
};


