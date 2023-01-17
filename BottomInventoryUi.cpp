#include "BottomInventoryUi.h"
#include "BottomInventoryCellUi.h"
#include "UiManager.h"
#include "Game.h"
#include "ItemData.h"
#include "Inventory.h"

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
	if (owner_ && owner_->get_inventory()) {
		OnInventoryDataChangedArgs args;
		args.sender = reinterpret_cast<DWORD_PTR>(this);
		owner_->get_inventory()->AddHandler([](Inventory* inventory, int index, ItemData* new_data, OnInventoryDataChangedArgs args) {
			BottomInventoryUi* p_self = reinterpret_cast<BottomInventoryUi*>(args.sender);
			p_self->ReloadData(index, new_data);
		}, args);
		CreateEmptyCells();
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
	UiManager::GetInstance()->SelectTarget(cells_[0]);
}

void BottomInventoryUi::Update()
{
	ImageUi::Update();


	if (owner_->IsDead()) owner_ = nullptr;

	
	if (! (Game::GetInstance()->get_game_state() & GAME_STATE_PLAYER_FREEZED)) {
		if (KEY_DOWN(KEY::KEY_1))	UiManager::GetInstance()->SelectTarget(cells_[0]);
		else if (KEY_DOWN(KEY::KEY_2))	UiManager::GetInstance()->SelectTarget(cells_[1]);
		else if (KEY_DOWN(KEY::KEY_3))	UiManager::GetInstance()->SelectTarget(cells_[2]);
		else if (KEY_DOWN(KEY::KEY_4))	UiManager::GetInstance()->SelectTarget(cells_[3]);
		else if (KEY_DOWN(KEY::KEY_5))	UiManager::GetInstance()->SelectTarget(cells_[4]);
		else if (KEY_DOWN(KEY::KEY_6))	UiManager::GetInstance()->SelectTarget(cells_[5]);
		else if (KEY_DOWN(KEY::KEY_7))	UiManager::GetInstance()->SelectTarget(cells_[6]);
		else if (KEY_DOWN(KEY::KEY_8))	UiManager::GetInstance()->SelectTarget(cells_[7]);
		else if (KEY_DOWN(KEY::KEY_9))	UiManager::GetInstance()->SelectTarget(cells_[8]);
		else if (KEY_DOWN(KEY::KEY_0))	UiManager::GetInstance()->SelectTarget(cells_[9]);
		else if (KEY_DOWN(KEY::KEY_MINUS))	UiManager::GetInstance()->SelectTarget(cells_[10]);
		else if (KEY_DOWN(KEY::KEY_PLUS))	UiManager::GetInstance()->SelectTarget(cells_[11]);
	}
	
	
	

	ChildrenUpdate();
}

void BottomInventoryUi::Render(ID3D11Device* p_d3d_device)
{
	ImageUi::Render(p_d3d_device);
	DrawRectangle(p_d3d_device, get_final_pos(), get_scale(), ARGB(0xFF00FF00), 1);

	ChildrenRender(p_d3d_device);
}
