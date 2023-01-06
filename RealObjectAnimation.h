#pragma once
#include "Animation.h"
class RealObjectAnimation : public Animation 
{
private:
	float depth_ = 1.f;
public:
	RealObjectAnimation();
	~RealObjectAnimation();
	// Animation��(��) ���� ��ӵ�
	virtual void Render(ID3D11Device* p_d3d_device) override;
	virtual void set_depth(float depth) { depth_ = depth; };
};


