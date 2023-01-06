#pragma once
#include "global.h"
#include "Animation.h"
class ItemAnimator;
class ItemAnimation : public Animation
{
public:
	ItemAnimation();
	virtual ~ItemAnimation();
private:
	ItemAnimator* animator_ = nullptr;
	float depth_ = 1.f;
public:


	// Animation을(를) 통해 상속됨
	inline void set_animator(ItemAnimator* animator) { animator_ = animator; };
	virtual void Render(ID3D11Device* p_d3d_device) override;
	inline void set_depth(float depth) { depth_ = depth; };

};

