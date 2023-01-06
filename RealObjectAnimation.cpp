#include "RealObjectAnimation.h"
#include "Animator.h"
#include "GObject.h"
#include "RealObject.h"

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
	switch (get_animator()->get_owner()->get_direction()) {
	case DIRECTION::LEFT: {
		direction = -1.f;
		} break;
	case DIRECTION::RIGHT: {
		direction = 1.f;
	} break;
	}

	if (!is_finished_) {
		RealObject* owner = dynamic_cast<RealObject*>(get_animator()->get_owner());
		if (owner && get_animator()) {
			Vector2 pos = WorldToRenderPos(owner->get_pos() + offset_);
			Vector2 scale = get_animator()->get_owner()->get_scale();
			const AnimationFrame& frame = frames_[frame_index_];
			DrawTexture(p_d3d_device
				, Vector2(pos.x - (get_animator()->get_owner()->get_scale().x / 2.f) * direction, pos.y - (get_animator()->get_owner()->get_scale().y / 2.f))
				, Vector2(scale.x * direction, scale.y)
				, frame.base_pos
				, frame.img_size
				, texture_
				, depth_);
		}
	}
	
	

}
