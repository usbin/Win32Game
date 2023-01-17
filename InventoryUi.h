#pragma once
#include "global.h"
#include "Ui.h"
class Player;
class InventoryCellUi;
class ItemData;
/// <summary>
/// I 누르면 열리는 인벤토리창.
/// - 화면에 꽉 참.
/// - 상단에 탭(인벤, 게임종료 탭만)
/// </summary>
class InventoryUi : public Ui
{

private:
	Player* owner_ = nullptr;
	
	Ui* child_ui_frame_body_ = nullptr;//프레임을 씌울 Ui
	InventoryCellUi* cells_[36] = {};//셀 Ui
	
	const Vector2 cell_offset_{35, 40};
	const Vector2 cell_size_{ 57, 57 };
	const float cell_distance_ = 3.f;

	InventoryCellUi* drag_start_cell_ = nullptr;
	
public:
	InventoryUi();
	void Init(Player* player);
	void ReloadData(int index, const ItemData* new_data);
	void Update() override;
	void Render(ID3D11Device* p_d3d_device) override;

	void SetDragStart(int index);
	void SetDragEnd(int index);
};

