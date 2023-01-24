#include "BottomInventoryUi.h"
#include "BottomInventoryCellUi.h"
#include "UiManager.h"
#include "Game.h"
#include "ItemData.h"
#include "Inventory.h"
#include "PlayerItemHolder.h"
BottomInventoryUi::BottomInventoryUi()
	: ImageUi(true)
{

}

BottomInventoryUi::~BottomInventoryUi()
{
	if(owner_ && owner_->get_inventory())
		owner_->get_inventory()->RemoveItemHandler(this);
}

void BottomInventoryUi::Init(Player* owner)
{
	owner_ = owner;
	if (owner_ && owner_->get_inventory()) {
		OnInventoryItemChangedArgs args;
		args.sender = reinterpret_cast<DWORD_PTR>(this);
		owner_->get_inventory()->AddItemHandler([](Inventory* inventory, int index, ItemData* new_data, OnInventoryItemChangedArgs args) {
			BottomInventoryUi* p_self = reinterpret_cast<BottomInventoryUi*>(args.sender);
			p_self->ReloadData(index, new_data);
		}, args);
		CreateEmptyCells();
		owner_->get_item_holder()->SetItem(0);
		const std::vector<ItemData*>& items = owner_->get_inventory()->GetItems();
		for (int i = 0; i < min(items.size(), CELL_COUNT_INLINE); i++) {
			ReloadData(i, items[i]);
		}
	}


}

void BottomInventoryUi::ReloadData(int index, const ItemData* new_data)
{
	if(index>=0 && index<CELL_COUNT_INLINE)
		cells_[index]->Reset(index, new_data);
}

void BottomInventoryUi::CreateEmptyCells()
{
	const float CELL_DISTANCE_PX = 4;//상하좌우 간격 2px
	for (int i = 0; i<CELL_COUNT_INLINE; i++) {
		BottomInventoryCellUi* cell = DEBUG_NEW BottomInventoryCellUi();
		//상하좌우 간격 CELL_DISTANCE_PX, 셀 크기는 남은공간/12 
		// -> 가로 길이: WIDTH - (2px*(CELL_COUNT+1))/12, 세로 길이: HEIGHT - 4px
		// -> 가로 위치: CELL_DISTANCE_PX + i*CELL_WIDTH, 세로 위치: CELL_DISTANCE_PXpx
		Vector2 cell_size{ (get_width() - (CELL_DISTANCE_PX * (CELL_COUNT_INLINE + 1))) / 12.f, get_height() - CELL_DISTANCE_PX*2.f};
		Vector2 cell_pos{ CELL_DISTANCE_PX + i * (cell_size.x+CELL_DISTANCE_PX), CELL_DISTANCE_PX };
		cell->set_pos(cell_pos);
		cell->set_scale(cell_size);
		cell->set_group_type(GROUP_TYPE::UI);
		cell->set_parent(this);
		cell->Init(this, i, nullptr);
		AddChild(cell);
		cells_[i] = cell;

	}
	picked_index_ = 0;
}

void BottomInventoryUi::Update()
{
	ImageUi::Update();


	if (owner_ && owner_->IsDead()) owner_ = nullptr;

	

	
	if (! CHECK_GAME_STATE(GAME_STATE_CONTROL_FREEZED)) {
		if (KEY_DOWN(KEY::KEY_1))	PickItem(0);
		else if (KEY_DOWN(KEY::KEY_2))	PickItem(1);
		else if (KEY_DOWN(KEY::KEY_3))	PickItem(2);
		else if (KEY_DOWN(KEY::KEY_4))	PickItem(3);
		else if (KEY_DOWN(KEY::KEY_5))	PickItem(4);
		else if (KEY_DOWN(KEY::KEY_6))	PickItem(5);
		else if (KEY_DOWN(KEY::KEY_7))	PickItem(6);
		else if (KEY_DOWN(KEY::KEY_8))	PickItem(7);
		else if (KEY_DOWN(KEY::KEY_9))	PickItem(8);
		else if (KEY_DOWN(KEY::KEY_0))	PickItem(9);
		else if (KEY_DOWN(KEY::KEY_MINUS))	PickItem(10);
		else if (KEY_DOWN(KEY::KEY_PLUS))	PickItem(11);
	}
	
	

}

void BottomInventoryUi::Render(ID3D11Device* p_d3d_device)
{
	ImageUi::Render(p_d3d_device);


	DrawRectangle(p_d3d_device, get_final_pos(), get_scale(), ARGB(0xFF00FF00), 1, RENDER_LAYER::PLAYER);

	ChildrenRender(p_d3d_device);
}

void BottomInventoryUi::PickItem(int index)
{
	picked_index_ = index;
	if (!owner_) return;
	if (!owner_->get_item_holder()) return;

	owner_->get_item_holder()->SetItem(index);
}

void BottomInventoryUi::OnDead()
{
	if (owner_ && owner_->get_inventory())
		owner_->get_inventory()->RemoveItemHandler(this);
}
