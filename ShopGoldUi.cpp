#include "ShopGoldUi.h"
#include "ShopUi.h"
#include "Decorator.h"
void ShopGoldUi::Init(ShopUi* shop_ui)
{
	if (shop_ui->get_player_inventory()) {
		gold_ = shop_ui->get_player_inventory()->GetGold();
		OnInventoryGoldChangedData on_gold_changed;
		on_gold_changed.args.sender = reinterpret_cast<DWORD_PTR>(this);
		on_gold_changed.handler = [](Inventory* inventory, UINT new_gold, OnInventoryGoldChangedArgs args){
			reinterpret_cast<ShopGoldUi*>(args.sender)->UpdateGold(new_gold);
		};
		shop_ui->get_player_inventory()->AddGoldHander(on_gold_changed.handler, on_gold_changed.args);
	}

}

void ShopGoldUi::Update()
{
	Ui::Update();
}

void ShopGoldUi::Render(ID3D11Device* p_d3d_device)
{
	Decorator::GetInstance()->GetSimpleFrame()->Render(p_d3d_device, this, RENDER_LAYER::PLAYER);
	TCHAR buffer[10];
	_stprintf_s(buffer, _T("%dG"), gold_);
	DrawFixedsizeText(p_d3d_device, get_final_pos(), get_scale() - Vector2{12, 0}
		,buffer, _tcslen(buffer), _T("µÕ±Ù¸ð²Ã"), 24
		, D2D1::ColorF::Black, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_TEXT_ALIGNMENT_TRAILING, DWRITE_PARAGRAPH_ALIGNMENT_CENTER, RENDER_LAYER::PLAYER);


	ChildrenRender(p_d3d_device);
}

void ShopGoldUi::UpdateGold(UINT gold)
{
	gold_ = gold;
}
