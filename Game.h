#pragma once
#include "global.h"
#include "Time.h"
class Player;
class InventoryUi;
class DebugConsoleUi;
class Loading;
class Game
{
private:
	SINGLETON(Game);

	GAME_STATE game_state_ = 0;
	//int player_freeze_count_=0;
	int time_stopped_count_=0;
	int control_freezed_count_ = 0;

	UINT day_ = 0;					//�������ΰ�
	float day_uptime_s_ = 0;			//���� �� ���� �Ϸ� 0�ú��� ����� �ð�

	
	InventoryUi* opened_inventory_ui_;
	DebugConsoleUi* opened_debug_console_ui_;
	Loading* opened_loading_ui_;
	
private:
	void Update();
	void Render(ID3D11Device* p_d3d_device);

public:
	void StartGame();									//1���� ���� �Լ�.
	void ShowDayFinishUi();
	void FinishDayProcess();							//�������� �ѱ�� ���μ��� ����(���ϻ��� ����, ��¥ ������Ʈ, �ð� �缳��)
	void SetTime(UINT day, UINT hour, UINT min);		//�ð� ���� �Լ�.
	UINT get_day_uptime_s() { return day_uptime_s_; };	//���� �� ���� �Ϸ� 0�ú��� ����� �ð�
	UINT get_day() { return day_; };					//�������ΰ�
	GAME_STATE get_game_state() { return game_state_; };
	//void PlayerFreeze();
	//void PlayerUnfreeze();
	void TimeFreeze();
	void TimeUnfreeze();
	void ControlFreeze();
	void ControlUnfreeze();

	//�κ��丮
	void ToggleInventory(Player* player);
	//������ ������
	void ToggleDebugConsole();
	//�ε� ȭ��
	void ShowLoading();
	void UnshowLoading();

	friend class Core;
	friend class TimerUi;
};

