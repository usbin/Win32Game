#pragma once
#include "Animation.h"
class RealObjectAnimation : public Animation 
{
public:
	RealObjectAnimation();
	~RealObjectAnimation();
	// Animation��(��) ���� ��ӵ�
	virtual void Render(ID3D11Device* p_d3d_device) override;
};


