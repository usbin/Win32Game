#include "BottomInventoryCellUi.h"
#include "UiSprite.h"
#include "IItem.h"
#include "ItemSprite.h"
#include "BottomInventoryUi.h"
#include "PlayerItemHolder.h"
#include "ItemData.h"
#include "TooltipUi.h"
#include "Decorator.h"
BottomInventoryCellUi::BottomInventoryCellUi()
	: ButtonUi(true)
{
}

BottomInventoryCellUi::~BottomInventoryCellUi()
{
	DeleteGObject(tooltip_, GROUP_TYPE::UI);
}

inline void BottomInventoryCellUi::Init(BottomInventoryUi* bottom_inventory_ui, int index, const ItemData* item_data)
{
	bottom_inventory_ui_ = bottom_inventory_ui;
	index_ = index;
	item_data_ = item_data;


	TooltipUi* tooltip = DEBUG_NEW TooltipUi(true);
	if (item_data && item_data->item) {
		tooltip->Init(item_data->item->get_item_description());
	}
	tooltip->set_group_type(GROUP_TYPE::UI);
	CreateGObject(tooltip, GROUP_TYPE::UI);
	tooltip_ = tooltip;
	tooltip_->set_enabled(false);
}

void BottomInventoryCellUi::Update()
{
	Ui::Update();
	if (tooltip_&&tooltip_->IsDead()) tooltip_ = nullptr;

	if (tooltip_) {
		tooltip_->set_enabled(get_mouse_on());
		tooltip_->set_pos(WorldToRenderPos(GET_MOUSE_POS()) - Vector2{0, 40});
	}
}

void BottomInventoryCellUi::Render(ID3D11Device* p_d3d_device)
{

	if (bottom_inventory_ui_) {
		Decorator::GetInstance()->GetInventoryCellFrame()->Render(p_d3d_device, this, RENDER_LAYER::PLAYER);
		if (bottom_inventory_ui_->get_picked_index() == index_) DrawRectangle(p_d3d_device, get_final_pos(), get_scale(), ARGB(0xFFFF0000), 3, RENDER_LAYER::PLAYER);
		if (item_data_ && item_data_->item) {
			const IItem* item = item_data_->item;
			if (item->get_sprite()) {
				DrawTexture(p_d3d_device, get_final_pos(), get_scale(), item->get_profile_sprite()->get_base_pos(), item->get_profile_sprite()->get_scale(), item->get_profile_sprite()->get_texture(), RENDER_LAYER::PLAYER);
				TCHAR amount[5] = _T("");
				_stprintf_s(amount, _T("%d"), item_data_->amount);
				DrawFixedsizeText(p_d3d_device, get_final_pos() + Vector2{ 3, 0 }, get_scale(), amount, _tcslen(amount), _T("µÕ±Ù¸ð²Ã"), 14
					, D2D1::ColorF::Black, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING, DWRITE_PARAGRAPH_ALIGNMENT_FAR, RENDER_LAYER::PLAYER);
				

				
			}

		}
		TCHAR shortcut[5] = _T("");
		switch (index_) {
		case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9: _stprintf_s(shortcut, _T("%d"), index_ + 1); break;
		case 10: _stprintf_s(shortcut, _T("-")); break;
		case 11: _stprintf_s(shortcut, _T("=")); break;
		}
		DrawFixedsizeText(p_d3d_device, get_final_pos() + Vector2{ -3, 0 }, get_scale(), shortcut, _tcslen(shortcut), _T("µÕ±Ù¸ð²Ã"), 16
			, D2D1::ColorF::Black, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT_NEAR, RENDER_LAYER::PLAYER);
	}
	ChildrenRender(p_d3d_device);
	
}

inline void BottomInventoryCellUi::Reset(int index, const ItemData* item_data)
{
	item_data_ = item_data;
	index_ = index;

	if (tooltip_ && item_data && item_data->item) {
		tooltip_->set_text(item_data->item->get_item_description());
	}
	else {
		tooltip_->set_text(_T(""));
	}
}

void BottomInventoryCellUi::LbuttonClick()
{
	if (bottom_inventory_ui_) {
		bottom_inventory_ui_->PickItem(index_);
	}
}
