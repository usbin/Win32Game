#pragma once
#include "global.h"
#include "Time.h"


class Game
{
private:
	SINGLETON(Game);

	GAME_STATE game_state_ = GAME_STATE::FREEZED;
	UINT day_ = 0;					//�������ΰ�
	UINT day_uptime_s_ = 0;			//���� �� ���� �Ϸ� 0�ú��� ����� �ð�
	float acc_dt_ = 0;				//1�ʸ� ����ϱ� ���� ���� ��

	
private:
	void Update();

public:
	void StartGame();									//1���� ���� �Լ�.
	void SetTime(UINT day, UINT hour, UINT min);		//�ð� ���� �Լ�.
	UINT get_day_uptime_s() { return day_uptime_s_; };
	UINT get_day() { return day_; };
	GAME_STATE get_game_state() { return game_state_; };
	void PlayerFreeze() { game_state_ = GAME_STATE::PLAYER_FREEZED; };
	void PlayerUnfreeze() { game_state_ = game_state_==GAME_STATE::FREEZED ? GAME_STATE::TIME_STOPPED : GAME_STATE::PLAYING; };

	friend class Core;
	friend class TimerUi;
};

