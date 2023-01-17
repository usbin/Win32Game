#pragma once
#include "global.h"
#include "Ui.h"
class Player;
class InventoryCellUi;
class ItemData;
/// <summary>
/// I ������ ������ �κ��丮â.
/// - ȭ�鿡 �� ��.
/// - ��ܿ� ��(�κ�, �������� �Ǹ�)
/// </summary>
class InventoryUi : public Ui
{

private:
	Player* owner_ = nullptr;
	
	Ui* child_ui_frame_body_ = nullptr;//�������� ���� Ui
	InventoryCellUi* cells_[36] = {};//�� Ui
	
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

