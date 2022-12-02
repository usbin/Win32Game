#pragma once
#include "global.h"
#include "Time.h"


class Game
{
private:
	SINGLETON(Game);

	GAME_STATE game_state_;
	UINT uptime_s;		//게임 속 1일차 0시부터 경과한 시간
	float acc_dt_;		//1초를 계산하기 위한 누적 값

	
private:
	void StartGame();	//1일차 시작 함수.
	void Update();

public:
	UINT get_uptime_s() { return uptime_s; };

	friend class Core;
	friend class TimerUi;
};

