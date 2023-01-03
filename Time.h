#pragma once
#include "global.h"

class Time {
	SINGLETON(Time);
private:
	HWND hwnd_ = 0;
	LARGE_INTEGER query_performance_frequency_; //�ʴ� ƽ��
	LARGE_INTEGER prev_tick_count_;				//���� ƽ ī��Ʈ
	double dt_ = 0;									//dt=1�����ӿ� �ɸ��� �ð�(s)
	double acc_dt_ = 0;								//���� dt
	int fps_ = 0;									//Frame Per Second : �ʴ� ������ ��
												//- 1/dt�� ������ �ʴ� ����: ��Ȯ��
public:
	bool Init(HWND h_wnd);
	bool Update();
	double dt_f() { return dt_; };
};