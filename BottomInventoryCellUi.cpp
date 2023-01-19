#include "BottomInventoryCellUi.h"
#include "UiSprite.h"
#include "IItem.h"
#include "ItemSprite.h"
#include "BottomInventoryUi.h"
#include "PlayerItemHolder.h"
#include "ItemData.h"
BottomInventoryCellUi::BottomInventoryCellUi()
	: ButtonUi(true)
{

}

BottomInventoryCellUi::~BottomInventoryCellUi()
{
}

inline void BottomInventoryCellUi::Init(BottomInventoryUi* bottom_inventory_ui, int index, const ItemData* item_data)
{
	bottom_inventory_ui_ = bottom_inventory_ui;
	index_ = index;
	item_data_ = item_data;
}

void BottomInventoryCellUi::Render(ID3D11Device* p_d3d_device)
{
	if (bottom_inventory_ui_) {
		if (bottom_inventory_ui_->get_picked_index() == index_) DrawRectangle(p_d3d_device, get_final_pos(), get_scale(), ARGB(0xFFFF0000), 1, RENDER_LAYER::TOP);
		else DrawRectangle(p_d3d_device, get_final_pos(), get_scale(), ARGB(0xFF00FF00), 1, RENDER_LAYER::TOP);
		if (item_data_ && item_data_->item) {
			const IItem* item = item_data_->item;
			if (item->get_sprite()) {
				DrawTexture(p_d3d_device, get_final_pos(), get_scale(), item->get_profile_sprite()->get_base_pos(), item->get_profile_sprite()->get_scale(), item->get_profile_sprite()->get_texture());
				TCHAR amount[5];
				_stprintf_s(amount, _T("%d"), item_data_->amount);
				DrawFixedsizeText(p_d3d_device, get_final_pos(), Vector2{ 40, 15 }, amount, _tcslen(amount), _T("µÕ±Ù¸ð²Ã"), 14
					, D2D1::ColorF::Black, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT_FAR);
			}

		}
	}
	
	
}

inline void BottomInventoryCellUi::Reset(int index, const ItemData* item_data)
{
	item_data_ = item_data;
	index_ = index;
}

void BottomInventoryCellUi::LbuttonClick()
{
	if (bottom_inventory_ui_) {
		bottom_inventory_ui_->PickItem(index_);
	}
}
