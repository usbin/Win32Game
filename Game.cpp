#include "Game.h"
#include "Player.h"
#include "InventoryUi.h"
Game::Game()
	: day_(1)
	, day_uptime_s_(0)
	, acc_dt_(0){};
Game::~Game() {};

void Game::StartGame()
{
	//게임 시작에 필요한 모든 로딩, 설정 끝낸 후
	acc_dt_ = 0.f;
	GameUnfreeze();
}

void Game::PlayerFreeze()
{
	game_state_ |= GAME_STATE_PLAYER_FREEZED;
	player_freeze_count_++;
}

void Game::PlayerUnfreeze()
{
	player_freeze_count_ = max(player_freeze_count_ - 1, 0);
	if (player_freeze_count_ == 0)
		game_state_ &= ~GAME_STATE_PLAYER_FREEZED;
}

void Game::GameFreeze()
{
	game_state_ |= (GAME_STATE_TIME_STOPPED | GAME_STATE_PLAYER_FREEZED);
	time_stopped_count_++; 
	player_freeze_count_++;
}

void Game::GameUnfreeze()
{
	player_freeze_count_ = max(player_freeze_count_ - 1, 0);
	time_stopped_count_ = max(time_stopped_count_ - 1, 0);
	if (time_stopped_count_ == 0 && player_freeze_count_ == 0) {
		game_state_ &= ~(GAME_STATE_TIME_STOPPED | GAME_STATE_PLAYER_FREEZED);
	}
}

void Game::ToggleInventory(Player* player)
{
	if (!opened_inventory_ui_) {
		GameFreeze();
		opened_inventory_ui_ = DEBUG_NEW InventoryUi();
		opened_inventory_ui_->Init(player);
		opened_inventory_ui_->set_group_type(GROUP_TYPE::UI);
		CreateGObject(opened_inventory_ui_, GROUP_TYPE::UI);
	}
	else {
		GameUnfreeze();
		DeleteGObject(opened_inventory_ui_, GROUP_TYPE::UI);
		opened_inventory_ui_ = nullptr;
	}
	
}

void Game::Update()
{
	if (!(game_state_ & GAME_STATE_TIME_STOPPED)) {
		acc_dt_ += DtF();
		day_uptime_s_ = acc_dt_;
	}
	

}
