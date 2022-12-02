#include "Time.h"

Time::Time()
	: hwnd_(0)
	, query_performance_frequency_({ 0 })
	, prev_tick_count_({ 0 })
	, dt_(0)
	, acc_dt_(0)
	, fps_(0) {

}
Time::~Time() {}
bool Time::Init(HWND h_wnd) {
	hwnd_ = h_wnd;
	QueryPerformanceFrequency(&query_performance_frequency_); //1초당 틱수
	QueryPerformanceCounter(&prev_tick_count_); //현재 틱수
	dt_ = acc_dt_ = 0.f;
	fps_ = 0;
	return TRUE;
}
bool Time::Update() {
	LARGE_INTEGER current_count;
	QueryPerformanceCounter(&current_count);
	dt_ = static_cast<double>(current_count.QuadPart - prev_tick_count_.QuadPart) / query_performance_frequency_.QuadPart;
#ifdef _DEBUG
	// dt는 이전 프레임에서 현재 프레임까지 걸린 시간.
	// dt가 작아지면=컴퓨터가 빠른 것=곱할 속도계수가 줄어듦.
	// dt가 커지면=컴퓨터가 느린 것=곱할 속도계수가 늘어남.
	// dt가 너무 커지면(ex: 디버깅 중 브레이크 포인트에 걸려있을 때 등) 속도계수가 너무 커지는 문제가 생김.
	// 따라서 dt가 너무 커져도 어느정도 이상 오르지 않도록 해야함.
	dt_ = min(dt_, 1.); //ms단위
#endif
	acc_dt_ += dt_;
	fps_++;
	if (acc_dt_ >= 1.f) {
		TCHAR buffer[100];
		_stprintf_s(buffer, _T("현재 FPS: %d, DT: %.10f"), fps_, dt_);
		SetWindowTextW(hwnd_, buffer);
		acc_dt_ = 0.f;
		fps_ = 0;
	}
	prev_tick_count_.QuadPart = current_count.QuadPart;

	return TRUE;
}