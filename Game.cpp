#include "Game.h"
#include "Player.h"
#include "InventoryUi.h"
#include "DebugConsoleUi.h"
#include "Core.h"
Game::Game()
	: day_(1)
	, day_uptime_s_(0)
	, acc_dt_(0){};
Game::~Game() {};

void Game::StartGame()
{
	//게임 시작에 필요한 모든 로딩, 설정 끝낸 후
	acc_dt_ = 0.f;
	PlayerUnfreeze();
	TimeUnfreeze();
	ControlUnfreeze();
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

void Game::TimeFreeze()
{
	game_state_ |= GAME_STATE_TIME_STOPPED;
	time_stopped_count_++; 
}

void Game::TimeUnfreeze()
{
	time_stopped_count_ = max(time_stopped_count_ - 1, 0);
	if (time_stopped_count_ == 0) {
		game_state_ &= ~GAME_STATE_TIME_STOPPED;
	}
}

void Game::ControlFreeze()
{
	game_state_ |= GAME_STATE_CONTROL_FREEZED;
	control_freezed_count_++;

}

void Game::ControlUnfreeze()
{
	control_freezed_count_ = max(control_freezed_count_ - 1, 0);
	if (control_freezed_count_ == 0) {
		game_state_ &= ~GAME_STATE_CONTROL_FREEZED;
	}
}

void Game::ToggleInventory(Player* player)
{
	if (!CHECK_GAME_STATE(GAME_STATE_CONTROL_FREEZED)) {
		if (!opened_inventory_ui_) {
			TimeFreeze();
			opened_inventory_ui_ = DEBUG_NEW InventoryUi();
			opened_inventory_ui_->Init(player);
			opened_inventory_ui_->set_group_type(GROUP_TYPE::UI);
			CreateGObject(opened_inventory_ui_, GROUP_TYPE::UI);
		}
		else {
			TimeUnfreeze();
			DeleteGObject(opened_inventory_ui_, GROUP_TYPE::UI);
			opened_inventory_ui_ = nullptr;
		}
	}
	
	
}

void Game::ToggleDebugConsole()
{
	if (!opened_debug_console_ui_) {
		ControlFreeze();
		opened_debug_console_ui_ = DEBUG_NEW DebugConsoleUi(true);
		opened_debug_console_ui_->set_pos(Vector2{ 100, 100 });
		opened_debug_console_ui_->set_scale(Core::GetInstance()->get_resolution() - opened_debug_console_ui_->get_pos()*2);
		opened_debug_console_ui_->Init();
		opened_debug_console_ui_->set_group_type(GROUP_TYPE::UI);
		CreateGObject(opened_debug_console_ui_, GROUP_TYPE::UI);
	}
	else {
		ControlUnfreeze();
		DeleteGObject(opened_debug_console_ui_, GROUP_TYPE::UI);
		opened_debug_console_ui_ = nullptr;
	}
}

void Game::Update()
{
	if (!(game_state_ & GAME_STATE_TIME_STOPPED)) {
		acc_dt_ += DtF();
		day_uptime_s_ = acc_dt_;
	}
	
	if (KEY_DOWN(KEY::KEY_GRAVE)) {
		ToggleDebugConsole();
	}

}
