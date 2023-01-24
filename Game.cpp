#include "Game.h"
#include "Player.h"
#include "InventoryUi.h"
#include "DebugConsoleUi.h"
#include "Core.h"
#include "ShippingBox.h"
#include "SceneManager.h"
#include "Inventory.h"
#include "DayFinishedUi.h"
Game::Game()
	: day_(1)
	, day_uptime_s_(0){
};
Game::~Game() {
	
};

void Game::StartGame()
{
	//====================
	// 게임 시작
	// ===================
	//게임 시작에 필요한 모든 로딩, 설정.
	day_ = 1;
	day_uptime_s_ = 6 * 60 * 60; //오전 6시로 셋팅
}

void Game::ShowDayFinishUi()
{
	DayFinishedUi* ui = DEBUG_NEW DayFinishedUi(true);
	ui->set_pos(Vector2::Zero());
	ui->set_scale(Core::GetInstance()->get_resolution());
	ui->set_name(_T("정산 화면 Ui"));
	ui->set_group_type(GROUP_TYPE::UI);
	ui->Init();
	CreateGObject(ui, GROUP_TYPE::UI);
}

void Game::FinishDayProcess()
{
	//========================
	// 날짜 넘기기 프로세스
	//========================
	// 출하상자 정산
	//------------------------
	// day 변수 ++
	//------------------------
	// 시간 재설정(기본값 6시)
	//------------------------

	//출하상자 정산
	const std::vector<GObject*>& gobjs_player = SceneManager::GetInstance()->get_current_scene()->GetGroupObjects(GROUP_TYPE::PLAYER);
	if (!gobjs_player.empty()) {
		Player* player = dynamic_cast<Player*>(gobjs_player[0]);
		const std::vector<GObject*>& gobjs_shipping_box = SceneManager::GetInstance()->GetAllShippingBoxes();
		//모든 출하상자의 아이템 정산
		UINT gold_sum = 0;
		for (int i = 0; i < gobjs_shipping_box.size(); i++) {
			ShippingBox* shipping_box = dynamic_cast<ShippingBox*>(gobjs_shipping_box[i]);
			gold_sum += shipping_box->CellItems();
		}
		//인벤토리에 정산 금액만큼 추가
		player->get_inventory()->AddGold(gold_sum);
	}

	day_++;

	day_uptime_s_ = 6 * 60 * 60;//시간 오전 6시로 셋팅
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

	//디버그 콘솔이 열려있지 않거나, enable이 false일 때 => 열기
	if (!opened_debug_console_ui_) {
		ControlFreeze();
		opened_debug_console_ui_ = DEBUG_NEW DebugConsoleUi(true);
		opened_debug_console_ui_->set_name(_T("Debug Console"));
		opened_debug_console_ui_->set_pos(Vector2{ 100, 100 });
		opened_debug_console_ui_->set_scale(Core::GetInstance()->get_resolution() - opened_debug_console_ui_->get_pos()*2);
		opened_debug_console_ui_->Init();
		opened_debug_console_ui_->set_group_type(GROUP_TYPE::UI);
		CreateGObject(opened_debug_console_ui_, GROUP_TYPE::UI);
	}
	else if (!opened_debug_console_ui_->get_enabled()) {
		ControlFreeze();
		opened_debug_console_ui_->set_enabled(true);
	}
	else {
		ControlUnfreeze();
		opened_debug_console_ui_->set_enabled(false);
	}
}

void Game::Update()
{
	if (!(game_state_ & GAME_STATE_TIME_STOPPED)) {
		day_uptime_s_ += DtF();
	}
	
	if (KEY_DOWN(KEY::KEY_GRAVE)) {
		ToggleDebugConsole();
	}
	if (opened_debug_console_ui_ && opened_debug_console_ui_->IsDead()) opened_debug_console_ui_ = nullptr;

}
