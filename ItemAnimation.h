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
	RENDER_LAYER layer_ = RENDER_LAYER::DEFAULT;
public:


	// Animation��(��) ���� ��ӵ�
	inline void set_animator(ItemAnimator* animator) { animator_ = animator; };
	virtual void Render(ID3D11Device* p_d3d_device) override;
	inline void set_layer(RENDER_LAYER layer) { layer_ = layer; };

};
