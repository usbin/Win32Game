#include "UiAnimation.h"
#include "Animator.h"
#include "Ui.h"

UiAnimation::UiAnimation()
{
}

UiAnimation::~UiAnimation()
{
}

void UiAnimation::Render(ID3D11Device* p_d3d_device)
{

	Ui* owner = dynamic_cast<Ui*>(animator_->get_owner());
	if (owner) {
		//현재 프레임 그리기
		Vector2 pos =  owner->get_final_pos() + offset_;
		if (!owner->is_static_pos()) pos = WorldToRenderPos(pos);

		const AnimationFrame& frame = frames_[frame_index_];
		DrawTexture(p_d3d_device, pos, animator_->get_owner()->get_scale(), frame.base_pos, frame.img_size, texture_);
	}
	

}
