#include "pch.h"
#include "Core.h"
#include "Time.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "PathManager.h"
#include "CollisionManager.h"
#include "EventManager.h"

Core::Core()
	: hwnd_(0)
	, hdc_(0)
	, hdc_mem_(0)
	, hbitmap_(0)
	, pt_resolution_(POINT{ 1024, 768 })
	, brushes{}
	, pens{}
	{

}

Core::~Core() {

}

//윈도우 닫히기 전 리소스 정리작업
int Core::OnDestroy() {
	ReleaseDC(hwnd_, hdc_);
	DeleteDC(hdc_mem_);
	DeleteObject(hbitmap_);
	//pen과 brush 삭제
	for (int i = 0; i < static_cast<int>(PEN_TYPE::END); i++) DeleteObject(pens[i]);
	for (int i = 0; i < static_cast<int>(BRUSH_TYPE::END); i++) DeleteObject(brushes[i]);
	return S_OK;
}


int Core::Init(HWND h_wnd, int width, int height) {
	
	//메모리 누수 체크
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(414);
	//_CrtSetBreakAlloc(430);



	hwnd_ = h_wnd;
	hdc_ = GetDC(hwnd_);
	RECT rect{ 0, 0, width, height };
	if (!AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, TRUE)) {
		return E_FAIL;
	}
	if (!SetWindowPos(h_wnd, nullptr, 100, 100, rect.right - rect.left, rect.bottom - rect.top, 0)) {
		return E_FAIL;
	}
	
	pt_resolution_ = POINT{ rect.right - rect.left, rect.bottom - rect.top };
	
	hbitmap_ = CreateCompatibleBitmap(hdc_, pt_resolution_.x, pt_resolution_.y);
	hdc_mem_ = CreateCompatibleDC(hdc_);
	HBITMAP org_bitmap = (HBITMAP) SelectObject(hdc_mem_, hbitmap_);
	DeleteObject(org_bitmap);


	InitPenAndBrush();
	Time::GetInstance()->Init(h_wnd);
	KeyManager::GetInstance()->Init();
	PathManager::GetInstance()->Init();
	SceneManager::GetInstance()->Init( hdc_mem_);
	CollisionManager::GetInstance()->Init();

	return S_OK;
}



bool Core::Progress()
{
	//===============
	//	선행작업
	//===============
	SyncResolution();
	Time::GetInstance()->Update();
	KeyManager::GetInstance()->Update();

	//===============
	//	메인 루틴
	//===============
	SceneManager::GetInstance()->Update();

	//===============
	//	마무리 루틴
	//===============
	CollisionManager::GetInstance()->Update();

	//===============
	//	화면 렌더링
	//===============
	SceneManager::GetInstance()->ClearView(hdc_mem_);
	SceneManager::GetInstance()->Render(hdc_mem_);
	BitBlt(hdc_, 0, 0, pt_resolution_.x, pt_resolution_.y, hdc_mem_, 0, 0, SRCCOPY);


	//===============
	//	이벤트 지연 처리
	//===============
	EventManager::GetInstance()->Update();

	return TRUE;
}



void Core::SyncResolution()
{
	RECT window_rect;
	GetWindowRect(hwnd_, &window_rect);
	if (pt_resolution_.x != window_rect.right - window_rect.left
		|| pt_resolution_.y != window_rect.bottom - window_rect.top) {
		pt_resolution_.x = window_rect.right - window_rect.left;
		pt_resolution_.y = window_rect.bottom - window_rect.top;

		hbitmap_ = CreateCompatibleBitmap(hdc_, pt_resolution_.x, pt_resolution_.y);
		HBITMAP org_bitmap = (HBITMAP)SelectObject(hdc_mem_, hbitmap_);
		DeleteObject(org_bitmap);

	}


}

void Core::InitPenAndBrush()
{
	pens[static_cast<int>(PEN_TYPE::BLACK)] = (HPEN)GetStockObject(BLACK_PEN);
	pens[static_cast<int>(PEN_TYPE::WHITE)] = (HPEN)GetStockObject(WHITE_PEN);
	pens[static_cast<int>(PEN_TYPE::RED)] = (HPEN)CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	pens[static_cast<int>(PEN_TYPE::GREEN)] = (HPEN)CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	pens[static_cast<int>(PEN_TYPE::BLUE)] = (HPEN)CreatePen(PS_SOLID, 1, RGB(0, 0, 255));

	brushes[static_cast<int>(BRUSH_TYPE::BLACK)] = (HBRUSH)GetStockObject(BLACK_BRUSH);
	brushes[static_cast<int>(BRUSH_TYPE::WHITE)] = (HBRUSH)GetStockObject(WHITE_BRUSH);
	brushes[static_cast<int>(BRUSH_TYPE::RED)] = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
	brushes[static_cast<int>(BRUSH_TYPE::GREEN)] = (HBRUSH)CreateSolidBrush(RGB(0, 255, 0));
	brushes[static_cast<int>(BRUSH_TYPE::BLUE)] = (HBRUSH)CreateSolidBrush(RGB(0, 0, 255));
	brushes[static_cast<int>(BRUSH_TYPE::HOLLOW)] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
}

