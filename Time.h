#pragma once

class Time {
	SINGLETON(Time);
private:
	HWND hwnd_;
	LARGE_INTEGER query_performance_frequency_; //초당 틱수
	LARGE_INTEGER prev_tick_count_;				//이전 틱 카운트
	double dt_;									//dt=1프레임에 걸리는 시간(s)
	double acc_dt_;								//누적 dt
	int fps_;									//Frame Per Second : 초당 프레임 수
												//- 1/dt로 구하지 않는 이유: 정확도
public:
	bool Init(HWND h_wnd);
	bool Update();
	double dt_f() { return dt_; };
};