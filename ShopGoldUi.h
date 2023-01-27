#pragma once
#include "global.h"
#include "Ui.h"
class ShopUi;
class ShopGoldUi : public Ui
{
	UINT gold_ = 0;
public:
	ShopGoldUi(bool is_static_pos) : Ui(is_static_pos) {};
	void Init(ShopUi* shop_ui);
	void Update();
	void Render(ID3D11Device* p_d3d_device);
	void UpdateGold(UINT gold);
};

