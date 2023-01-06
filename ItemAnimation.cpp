#include "ItemAnimation.h"
#include "ItemAnimator.h"
#include "RealObject.h"
#include "IItemHolder.h"
#include "IItem.h"
ItemAnimation::ItemAnimation()
{
}
ItemAnimation::~ItemAnimation()
{
}
void ItemAnimation::Render(ID3D11Device* p_d3d_device)
{
	if (!is_finished() && animator_) {
		IItemHolder* item = animator_->get_owner();
		if (item && animator_) {
			const AnimationFrame& frame = frames_[frame_index_];
			RealObject* owner = item->get_owner();
			Vector2 pos = item->get_hold_offset() + WorldToRenderPos(owner->get_pos());
			Vector2 scale = item->get_item()->get_scale();
			float direction = owner->get_direction() == DIRECTION::LEFT ? -1.f : 1.f;

			DrawTexture(p_d3d_device
				, Vector2(pos.x - (scale.x/ 2.f) * direction, pos.y - scale.y / 2.f)
				, Vector2(scale.x * direction, scale.y)
				, frame.base_pos
				, frame.img_size
				, texture_, layer_);
		}
	}
}
