#pragma once
#include "global.h"
#include "Time.h"


class Game
{
private:
	SINGLETON(Game);

	GAME_STATE game_state_;
	UINT day_ = 0;					//몇일차인가
	UINT day_uptime_s_ = 0;			//게임 속 오늘 하루 0시부터 경과한 시간
	float acc_dt_ = 0;				//1초를 계산하기 위한 누적 값

	
private:
	void Update();

public:
	void StartGame();									//1일차 시작 함수.
	void SetTime(UINT day, UINT hour, UINT min);		//시간 설정 함수.
	UINT get_day_uptime_s() { return day_uptime_s_; };
	UINT get_day() { return day_; };

	friend class Core;
	friend class TimerUi;
};

