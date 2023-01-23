#include "InventoryCellUi.h"
#include "Decorator.h"
#include "ItemData.h"
#include "IItem.h"
#include "ItemSprite.h"
#include "InventoryUi.h"
#include "TooltipUi.h"
InventoryCellUi::~InventoryCellUi()
{
}
void InventoryCellUi::Init(InventoryUi* inventory_ui, int index, const ItemData* item_data)
{
	inventory_ui_ = inventory_ui;
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
void InventoryCellUi::Reset(const ItemData* item_data)
{
	item_data_ = item_data;
	if (item_data && item_data->item) {
		tooltip_->set_text(item_data->item->get_item_description());
	}
	else {
		tooltip_->set_text(_T(""));
	}
}
void InventoryCellUi::Update()
{
	ButtonUi::Update();


	if (inventory_ui_ && inventory_ui_->IsDead()) inventory_ui_ = nullptr;
	if (tooltip_->IsDead()) tooltip_ = nullptr;

	if (tooltip_) {
		tooltip_->set_enabled(get_mouse_on());
		tooltip_->set_pos(WorldToRenderPos(GET_MOUSE_POS()));
	}
	
}
void InventoryCellUi::Render(ID3D11Device* p_d3d_device)
{
	Decorator::GetInstance()->GetInventoryCellFrame()->Render(p_d3d_device, this, RENDER_LAYER::PLAYER);

	if (item_data_ && item_data_->item) {
		const IItem* item = item_data_->item;
		if (item->get_sprite()) {
			DrawTexture(p_d3d_device, get_final_pos(), get_scale(), item->get_profile_sprite()->get_base_pos(), item->get_profile_sprite()->get_scale(), item->get_profile_sprite()->get_texture(), RENDER_LAYER::PLAYER);
			TCHAR amount[5];
			_stprintf_s(amount, _T("%d"), item_data_->amount);
			DrawFixedsizeText(p_d3d_device, get_final_pos(), Vector2{ 40, 15 }, amount, _tcslen(amount), _T("µÕ±Ù¸ð²Ã"), 14
				, D2D1::ColorF::Black, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT_FAR, RENDER_LAYER::PLAYER);
		}

	}
}

void InventoryCellUi::LbuttonDown()
{
	if (inventory_ui_) {
		inventory_ui_->SetDragStart(index_);
	}
}

void InventoryCellUi::LbuttonUp()
{
	if (inventory_ui_) {
		inventory_ui_->SetDragEnd(index_);
	}
}
