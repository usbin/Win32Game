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
	QueryPerformanceFrequency(&query_performance_frequency_); //1�ʴ� ƽ��
	QueryPerformanceCounter(&prev_tick_count_); //���� ƽ��
	dt_ = acc_dt_ = 0.f;
	fps_ = 0;
	return TRUE;
}
bool Time::Update() {
	LARGE_INTEGER current_count;
	QueryPerformanceCounter(&current_count);
	dt_ = static_cast<double>(current_count.QuadPart - prev_tick_count_.QuadPart) / query_performance_frequency_.QuadPart;
#ifdef _DEBUG
	// dt�� ���� �����ӿ��� ���� �����ӱ��� �ɸ� �ð�.
	// dt�� �۾�����=��ǻ�Ͱ� ���� ��=���� �ӵ������ �پ��.
	// dt�� Ŀ����=��ǻ�Ͱ� ���� ��=���� �ӵ������ �þ.
	// dt�� �ʹ� Ŀ����(ex: ����� �� �극��ũ ����Ʈ�� �ɷ����� �� ��) �ӵ������ �ʹ� Ŀ���� ������ ����.
	// ���� dt�� �ʹ� Ŀ���� ������� �̻� ������ �ʵ��� �ؾ���.
	dt_ = min(dt_, 1.); //ms����
#endif
	acc_dt_ += dt_;
	fps_++;
	if (acc_dt_ >= 1.f) {
		TCHAR buffer[100];
		_stprintf_s(buffer, _T("���� FPS: %d, DT: %.10f"), fps_, dt_);
		SetWindowTextW(hwnd_, buffer);
		acc_dt_ = 0.f;
		fps_ = 0;
	}
	prev_tick_count_.QuadPart = current_count.QuadPart;

	return TRUE;
}