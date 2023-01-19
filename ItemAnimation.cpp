#include "ItemAnimation.h"
#include "ItemAnimator.h"
#include "RealObject.h"
#include "IItemHolder.h"
#include "IItem.h"
#include "ItemData.h"
ItemAnimation::ItemAnimation()
{
}
ItemAnimation::~ItemAnimation()
{
}
void ItemAnimation::Render(ID3D11Device* p_d3d_device)
{
	if (!is_finished() && animator_) {
		IItemHolder* item_holder = animator_->get_owner();
		if (item_holder && animator_) {
			const ItemData* item_data = item_holder->GetItemData();
			if (item_data) {
				const AnimationFrame& frame = frames_[frame_index_];
				RealObject* owner = item_holder->get_owner();
				Vector2 pos = item_holder->get_hold_offset() + WorldToRenderPos(owner->get_pos());
				Vector2 scale = item_data->item->get_scale();
				float direction = owner->get_direction() == DIRECTION::LEFT ? -1.f : 1.f;

				DrawTexture(p_d3d_device
					, Vector2(pos.x - (scale.x / 2.f) * direction, pos.y - scale.y / 2.f)
					, Vector2(scale.x * direction, scale.y)
					, frame.base_pos
					, frame.img_size
					, texture_, layer_);
			}
			
		}
	}
}
