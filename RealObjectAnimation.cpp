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

	//현재 프레임 그리기
	float direction = 1.f;
	switch (animator_->get_owner()->get_direction()) {
	case DIRECTION::LEFT: {
		direction = 1.f;
		}
						break;
	case DIRECTION::RIGHT: {
		direction = -1.f;
	}
						 break;
	}

	GObject* owner = animator_->get_owner();
	Vector2 pos = WorldToRenderPos(owner->get_pos() + offset_);
	Vector2 scale = animator_->get_owner()->get_scale();
	const AnimationFrame& frame = frames_[frame_index_];
	DrawTexture(p_d3d_device
		, Vector2(pos.x - (animator_->get_owner()->get_scale().x / 2.f) * direction, pos.y - (animator_->get_owner()->get_scale().y / 2.f))
		, Vector2(scale.x * direction, scale.y)
		, frame.base_pos
		, frame.img_size
		, texture_);



}
