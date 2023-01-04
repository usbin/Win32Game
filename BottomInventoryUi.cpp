#include "BottomInventoryUi.h"
#include "BottomInventoryCellUi.h"

BottomInventoryUi::BottomInventoryUi()
	: ImageUi(true)
{
}

BottomInventoryUi::~BottomInventoryUi()
{
}

void BottomInventoryUi::Init(Player* owner)
{
	owner_ = owner;
}

void BottomInventoryUi::CreateEmptyCells()
{
	const float CELL_DISTANCE_PX = 4;//�����¿� ���� 2px
	for (int i = 0; i<CELL_COUNT; i++) {
		BottomInventoryCellUi* cell = DEBUG_NEW BottomInventoryCellUi();
		//�����¿� ���� CELL_DISTANCE_PX, �� ũ��� ��������/12 
		// -> ���� ����: WIDTH - (2px*(CELL_COUNT+1))/12, ���� ����: HEIGHT - 4px
		// -> ���� ��ġ: CELL_DISTANCE_PX + i*CELL_WIDTH, ���� ��ġ: CELL_DISTANCE_PXpx
		Vector2 cell_size{ (get_width() - (CELL_DISTANCE_PX * (CELL_COUNT + 1))) / 12.f, get_height() - CELL_DISTANCE_PX*2.f};
		Vector2 cell_pos{ CELL_DISTANCE_PX + i * (cell_size.x+CELL_DISTANCE_PX), CELL_DISTANCE_PX };
		cell->set_pos(cell_pos);
		cell->set_scale(cell_size);
		cell->set_group_type(GROUP_TYPE::UI);
		cell->set_parent(this);
		cell->Init(this);
		AddChild(cell);
		cell->AddOnClickHandler([](DWORD_PTR p_self, DWORD_PTR p2) {
			BottomInventoryCellUi* cell = reinterpret_cast<BottomInventoryCellUi*>(p_self);
			cell->Select();
			}, reinterpret_cast<DWORD_PTR>(cell), 0);
		cells_[i] = cell;

	}
}

void BottomInventoryUi::Update()
{
	if (owner_->IsDead()) owner_ = nullptr;

	ImageUi::Update();
	if (owner_) {
		//������ ����Ʈ�� ������.
		const std::vector<ItemData>& inventory = owner_->get_inventory();
		//cells ����
		for (int i = 0; i < min(inventory.size(), CELL_COUNT); i++) {
			cells_[i]->SetItem(inventory[i]);
		}
	}

	ChildrenUpdate();
}

void BottomInventoryUi::Render(ID3D11Device* p_d3d_device)
{
	ImageUi::Render(p_d3d_device);
	DrawRectangle(p_d3d_device, get_final_pos(), get_scale(), ARGB(0xFF00FF00));

	ChildrenRender(p_d3d_device);
}
