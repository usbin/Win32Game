#include "ShopItemCellUi.h"
#include "ShopUi.h"
#include "IItem.h"
#include "ItemSprite.h"
#include "TooltipUi.h"
#include "FmodSound.h"
#include "ResManager.h"
void ShopItemCellUi::Init(ShopUi* shop_ui, const IItem* item)
{
	item_ = item;

	TooltipUi* tooltip = DEBUG_NEW TooltipUi(true);
	tooltip->Init(item_->get_item_description());
	tooltip->set_parent(this);
	tooltip->set_enabled(false);
	AddChild(tooltip);
	tooltip_ = tooltip;

	shop_ui_ = shop_ui;
}

void ShopItemCellUi::Update()
{
	Ui::Update();
	if (shop_ui_ && shop_ui_->IsDead()) shop_ui_ = nullptr;
	//툴팁
	if (tooltip_ && tooltip_->IsDead()) tooltip_ = nullptr;

	if (tooltip_) {
		tooltip_->set_enabled(get_mouse_on());
		tooltip_->set_pos(WorldToRenderPos(GET_MOUSE_POS()) - get_final_pos());
	}

	
}

void ShopItemCellUi::Render(ID3D11Device* p_d3d_device)
{
	// 이미지 | 이름 | 가격
	DrawTexture(p_d3d_device, get_final_pos(), Vector2{ 32, 32 }, 
		item_->get_profile_sprite()->get_base_pos(), item_->get_profile_sprite()->get_scale(), item_->get_profile_sprite()->get_texture(), RENDER_LAYER::PLAYER);

	DrawFixedsizeText(p_d3d_device, get_final_pos() + Vector2{ 32 + 10, 0 }, Vector2{ 200, 32 }
		, item_->get_item_name().c_str(), item_->get_item_name().size()+1, _T("둥근모꼴"), 24
		, D2D1::ColorF::Black, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT_CENTER, RENDER_LAYER::PLAYER);
	
	TCHAR buffer[10];
	_stprintf_s(buffer, _T("%dG"), item_->get_price());
	DrawFixedsizeText(p_d3d_device, get_final_pos() + Vector2{ 32 + 10 + 100 + 10, 0 }, Vector2{80, 32}
		, buffer, _tcslen(buffer), _T("둥근모꼴"), 24
		, D2D1::ColorF::Black, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING, DWRITE_PARAGRAPH_ALIGNMENT_CENTER, RENDER_LAYER::PLAYER);

	
	ChildrenRender(p_d3d_device);
	
}

void ShopItemCellUi::LbuttonClick()
{
	//돈이 있다면 구매 처리
	if (shop_ui_ && shop_ui_->get_player_inventory()) {
		if (shop_ui_->get_player_inventory()->GetGold() >= item_->get_price()) {
			shop_ui_->get_player_inventory()->AddItem(item_, 1);
			shop_ui_->get_player_inventory()->RemoveGold(item_->get_price());
			Sound* sound = ResManager::GetInstance()->LoadSound(_T("Buy Effect"), _T("sound\\Buy_Effect.wav"));
			FmodSound::GetInstance()->Play(FmodSound::GetInstance()->GetChannel(), sound, false);

		}
	}
}
