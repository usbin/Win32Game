#include "RealObjectAnimation.h"
#include "Animator.h"
#include "GObject.h"

RealObjectAnimation::RealObjectAnimation()
{
}

RealObjectAnimation::~RealObjectAnimation()
{
}

void RealObjectAnimation::Render(ID3D11Device* p_d3d_device)
{

	//���� ������ �׸���
	const Vector2& pos = WorldToRenderPos(animator_->get_owner()->get_pos() + offset_);

	const AnimationFrame& frame = frames_[frame_index_];
	DrawTexture(p_d3d_device, pos - animator_->get_owner()->get_scale() / 2.f, animator_->get_owner()->get_scale(), frame.base_pos, frame.img_size, texture_);



}
