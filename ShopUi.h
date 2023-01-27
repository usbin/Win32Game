#pragma once
#include "global.h"
#include "Ui.h"
#include "ShopItemCellUi.h"
#include "ShopGoldUi.h"
#include "ShopInventoryUi.h"
#include "IItem.h"
#include "Inventory.h"
#include "Player.h"
class ShopUi : public Ui
{
	Ui* item_cell_container_ = nullptr;
	std::vector<ShopItemCellUi*> item_cells_;
	ShopGoldUi* gold_ui_ = nullptr;
	ShopInventoryUi* inventory_ui_ = nullptr;

	std::vector<const IItem*> items_;
	const Player* owner_ = nullptr;

public:

	ShopUi(bool is_static_pos) : Ui(is_static_pos) {};
	~ShopUi();
	void Init(const Player* player);
	void Update();
	void Render(ID3D11Device* p_d3d_device);

	Inventory* get_player_inventory() { return owner_? owner_->get_inventory(): nullptr; };
};

