#pragma once
#include "global.h"
#include "ButtonUi.h"
#include "IItem.h"
class BottomInventoryUi;
class ItemData;
class BottomInventoryCellUi : public ButtonUi
{
public:
	BottomInventoryCellUi();
	~BottomInventoryCellUi();

private:
	const ItemData* item_data_ = nullptr;
	BottomInventoryUi* bottom_inventory_ui_ = nullptr;
	int index_ = -1;

public:
	inline void Init(BottomInventoryUi* bottom_inventory_ui, int index, const ItemData* item_data);
	virtual void Render(ID3D11Device* p_d3d_device) override;
	inline void Reset(int index, const ItemData* item_data);
	virtual void LbuttonClick() override;
};

