#pragma once
#include "global.h"
#include "Time.h"


class Game
{
private:
	SINGLETON(Game);

	GAME_STATE game_state_;
	UINT day_;					//�������ΰ�
	UINT day_uptime_s_;			//���� �� ���� �Ϸ� 0�ú��� ����� �ð�
	float acc_dt_;				//1�ʸ� ����ϱ� ���� ���� ��

	
private:
	void Update();

public:
	void StartGame();									//1���� ���� �Լ�.
	void SetTime(UINT day, UINT hour, UINT min);		//�ð� ���� �Լ�.
	UINT get_day_uptime_s() { return day_uptime_s_; };
	UINT get_day() { return day_; };

	friend class Core;
	friend class TimerUi;
};

