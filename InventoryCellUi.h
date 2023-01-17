#pragma once
#include "global.h"
#include "ButtonUi.h";
class InventoryUi;
class ItemData;
class InventoryCellUi : public ButtonUi
{
private:
	InventoryUi* inventory_ui_ = nullptr;
	int index_ = -1;
	const ItemData* item_data_ = nullptr;
public:
	InventoryCellUi(bool is_static_pos) : ButtonUi(is_static_pos) {};
	void Init(InventoryUi* inventory_ui, int index, const ItemData* item_data);
	void Reset(const ItemData* item_data);
	void Update() override;
	void Render(ID3D11Device* p_d3d_device) override;
	const ItemData* get_item_data() { return item_data_; };
	int get_index() { return index_; };
	void LbuttonDown() override;
	void LbuttonUp() override;
};

