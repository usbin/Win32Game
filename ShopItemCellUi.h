#pragma once
#include "global.h"
#include "ButtonUi.h"
class ShopUi;
class IItem;
class TooltipUi;
class ShopItemCellUi : public ButtonUi
{
private:
	const IItem* item_ = nullptr;
	TooltipUi* tooltip_ = nullptr;

	UINT buy_amount_ = 0;

	ShopUi* shop_ui_ = nullptr;
public:
	ShopItemCellUi(bool is_static_pos) : ButtonUi(is_static_pos) {};
	void Init(ShopUi* shop_ui, const IItem* item);
	void Update();
	void Render(ID3D11Device* p_d3d_device);
	void LbuttonClick() override;
};

