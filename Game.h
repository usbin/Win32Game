#pragma once
#include "global.h"
#include "Time.h"
class Player;
class InventoryUi;
class Game
{
private:
	SINGLETON(Game);

	GAME_STATE game_state_ = GAME_STATE_TIME_STOPPED | GAME_STATE_PLAYER_FREEZED;
	int player_freeze_count_=0;
	int time_stopped_count_=0;

	UINT day_ = 0;					//�������ΰ�
	UINT day_uptime_s_ = 0;			//���� �� ���� �Ϸ� 0�ú��� ����� �ð�
	float acc_dt_ = 0;				//1�ʸ� ����ϱ� ���� ���� ��

	
	InventoryUi* opened_inventory_ui_;
	
private:
	void Update();

public:
	void StartGame();									//1���� ���� �Լ�.
	void SetTime(UINT day, UINT hour, UINT min);		//�ð� ���� �Լ�.
	UINT get_day_uptime_s() { return day_uptime_s_; };
	UINT get_day() { return day_; };
	GAME_STATE get_game_state() { return game_state_; };
	void PlayerFreeze();
	void PlayerUnfreeze();
	void GameFreeze();
	void GameUnfreeze();

	//�κ��丮
	void ToggleInventory(Player* player);

	friend class Core;
	friend class TimerUi;
};

