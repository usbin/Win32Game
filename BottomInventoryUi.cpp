#include "BottomInventoryUi.h"
#include "BottomInventoryCellUi.h"
#include "UiManager.h"
#include "Game.h"

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
	const float CELL_DISTANCE_PX = 4;//상하좌우 간격 2px
	for (int i = 0; i<CELL_COUNT; i++) {
		BottomInventoryCellUi* cell = DEBUG_NEW BottomInventoryCellUi();
		//상하좌우 간격 CELL_DISTANCE_PX, 셀 크기는 남은공간/12 
		// -> 가로 길이: WIDTH - (2px*(CELL_COUNT+1))/12, 세로 길이: HEIGHT - 4px
		// -> 가로 위치: CELL_DISTANCE_PX + i*CELL_WIDTH, 세로 위치: CELL_DISTANCE_PXpx
		Vector2 cell_size{ (get_width() - (CELL_DISTANCE_PX * (CELL_COUNT + 1))) / 12.f, get_height() - CELL_DISTANCE_PX*2.f};
		Vector2 cell_pos{ CELL_DISTANCE_PX + i * (cell_size.x+CELL_DISTANCE_PX), CELL_DISTANCE_PX };
		cell->set_pos(cell_pos);
		cell->set_scale(cell_size);
		cell->set_group_type(GROUP_TYPE::UI);
		cell->set_parent(this);
		cell->Init(this);
		AddChild(cell);
		cells_[i] = cell;

	}
}

void BottomInventoryUi::Update()
{
	if (owner_->IsDead()) owner_ = nullptr;

	ImageUi::Update();
	if (owner_) {
		//아이템 리스트를 가져옴.
		const std::vector<ItemData>& inventory = owner_->get_inventory();
		//cells 설정
		for (int i = 0; i < min(inventory.size(), CELL_COUNT); i++) {
			cells_[i]->SetItem(inventory[i]);
		}
	}
	switch (Game::GetInstance()->get_game_state())
	{
	case GAME_STATE::PLAYING:
	case GAME_STATE::TIME_STOPPED:
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
		break;
	case GAME_STATE::PLAYER_FREEZED:
	case GAME_STATE::FREEZED:
		break;
	}
	
	

	ChildrenUpdate();
}

void BottomInventoryUi::Render(ID3D11Device* p_d3d_device)
{
	ImageUi::Render(p_d3d_device);
	DrawRectangle(p_d3d_device, get_final_pos(), get_scale(), ARGB(0xFF00FF00));

	ChildrenRender(p_d3d_device);
}
