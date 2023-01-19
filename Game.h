#pragma once
#include "global.h"
#include "Time.h"
class Player;
class InventoryUi;
class DebugConsoleUi;
class Game
{
private:
	SINGLETON(Game);

	GAME_STATE game_state_ = 0;
	int player_freeze_count_=0;
	int time_stopped_count_=0;
	int control_freezed_count_ = 0;

	UINT day_ = 0;					//몇일차인가
	float day_uptime_s_ = 0;			//게임 속 오늘 하루 0시부터 경과한 시간

	
	InventoryUi* opened_inventory_ui_;
	DebugConsoleUi* opened_debug_console_ui_;

	
private:
	void Update();

public:
	void StartGame();									//1일차 시작 함수.
	void FinishDay();									//다음날로 넘기는 함수.(출하상자 정산, 날짜 업데이트, 시간 재설정)
	void SetTime(UINT day, UINT hour, UINT min);		//시간 설정 함수.
	UINT get_day_uptime_s() { return day_uptime_s_; };	//게임 속 오늘 하루 0시부터 경과한 시간
	UINT get_day() { return day_; };					//몇일차인가
	GAME_STATE get_game_state() { return game_state_; };
	void PlayerFreeze();
	void PlayerUnfreeze();
	void TimeFreeze();
	void TimeUnfreeze();
	void ControlFreeze();
	void ControlUnfreeze();

	//인벤토리
	void ToggleInventory(Player* player);
	//관리자 윈도우
	void ToggleDebugConsole();

	friend class Core;
	friend class TimerUi;
};

