#pragma once
#include "global.h"
#include "ButtonUi.h"
#include "IItem.h"
class BottomInventoryUi;
class BottomInventoryCellUi : public ButtonUi
{
public:
	BottomInventoryCellUi();
	~BottomInventoryCellUi();

private:
	ItemData item_data_ = {nullptr, 0};
	BottomInventoryUi* bottom_inventory_ui_;

public:
	void Init(BottomInventoryUi* bottom_inventory_ui) { bottom_inventory_ui_ = bottom_inventory_ui; };
	virtual void Render(ID3D11Device* p_d3d_device) override;
	inline void SetItem(ItemData item_data) { item_data_ = item_data; };
	virtual void Select() override;
};

