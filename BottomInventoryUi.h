#pragma once
#include "global.h"
#include "ImageUi.h"
#include "Player.h"
class BottomInventoryCellUi;
class ItemData;

class BottomInventoryUi : public ImageUi
{
public:
	BottomInventoryUi();
	~BottomInventoryUi();

private:
	BottomInventoryCellUi* cells_[static_cast<int>(KEY::KEY_PLUS) - static_cast<int>(KEY::KEY_1) + 1]; //1번부터 +까지
	Player* owner_;
	int picked_index_ = 0;

public:
	void Init(Player* owner);
	void ReloadData(int index, const ItemData* new_data);
	void CreateEmptyCells();
	virtual void Update() override;
	virtual void Render(ID3D11Device* p_d3d_device) override;
	inline Player* get_owner() { return owner_; };
	void PickItem(int index);
	inline int get_picked_index() { return picked_index_; };
	void OnDead() override;
};

