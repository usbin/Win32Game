#pragma once

class Time {
	SINGLETON(Time);
private:
	HWND hwnd_;
	LARGE_INTEGER query_performance_frequency_; //�ʴ� ƽ��
	LARGE_INTEGER prev_tick_count_;				//���� ƽ ī��Ʈ
	double dt_;									//dt=1�����ӿ� �ɸ��� �ð�(s)
	double acc_dt_;								//���� dt
	int fps_;									//Frame Per Second : �ʴ� ������ ��
												//- 1/dt�� ������ �ʴ� ����: ��Ȯ��
public:
	bool Init(HWND h_wnd);
	bool Update();
	double dt_f() { return dt_; };
};