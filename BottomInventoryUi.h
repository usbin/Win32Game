#pragma once
#include "global.h"
#include "ImageUi.h"
#include "Player.h"
class BottomInventoryCellUi;

class BottomInventoryUi : public ImageUi
{
public:
	BottomInventoryUi();
	~BottomInventoryUi();

private:
	const float CELL_COUNT = (static_cast<int>(KEY::KEY_PLUS) - static_cast<int>(KEY::KEY_1) + 1);
	BottomInventoryCellUi* cells_[static_cast<int>(KEY::KEY_PLUS) - static_cast<int>(KEY::KEY_1) + 1]; //1번부터 +까지
	Player* owner_;

public:
	void Init(Player* owner);
	void CreateEmptyCells();
	virtual void Update() override;
	virtual void Render(ID3D11Device* p_d3d_device) override;
	inline Player* get_owner() { return owner_; };
};

