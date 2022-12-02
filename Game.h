#pragma once
#include "global.h"
#include "Time.h"


class Game
{
private:
	SINGLETON(Game);

	GAME_STATE game_state_;
	UINT uptime_s;		//���� �� 1���� 0�ú��� ����� �ð�
	float acc_dt_;		//1�ʸ� ����ϱ� ���� ���� ��

	
private:
	void StartGame();	//1���� ���� �Լ�.
	void Update();

public:
	UINT get_uptime_s() { return uptime_s; };

	friend class Core;
	friend class TimerUi;
};

