#include "BottomInventoryCellUi.h"
#include "UiSprite.h"
#include "IItem.h"
#include "ItemSprite.h"
#include "BottomInventoryUi.h"
#include "PlayerItemHolder.h"
BottomInventoryCellUi::BottomInventoryCellUi()
	: ButtonUi(true)
{
	set_is_selectable(true);

}

BottomInventoryCellUi::~BottomInventoryCellUi()
{
}

void BottomInventoryCellUi::Render(ID3D11Device* p_d3d_device)
{
	if(get_selected()) DrawRectangle(p_d3d_device, get_final_pos(), get_scale(), ARGB(0xFFFF0000), RENDER_LAYER::TOP);
	else DrawRectangle(p_d3d_device, get_final_pos(), get_scale(), ARGB(0xFF00FF00), RENDER_LAYER::TOP);
	if (item_data_.item) {
		const IItem* item = item_data_.item;
		if (item->get_sprite()) {
			DrawTexture(p_d3d_device, get_final_pos(), get_scale(), item->get_sprite()->get_base_pos(), item->get_sprite()->get_scale(), item->get_sprite()->get_texture());
		}

	}
	
}

void BottomInventoryCellUi::Select()
{
	if (!bottom_inventory_ui_) return;
	if (!bottom_inventory_ui_->get_owner()) return;
	if (!bottom_inventory_ui_->get_owner()->get_item_holder()) return;

	bottom_inventory_ui_->get_owner()->get_item_holder()->SetItem(item_data_.item);
}
