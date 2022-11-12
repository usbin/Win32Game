#include "Core.h"
#include "Time.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "PathManager.h"
#include "CollisionManager.h"
#include "EventManager.h"
#include "Camera.h"
#include "UiManager.h"

Core::Core()
	: hwnd_(0)
	, hdc_(0)
	, hdc_mem_(0)
	, hbitmap_(0)
	, pt_resolution_(POINT{ 1024, 768 })
	, brushes{}
	, pens{}
	, p_d3d_{nullptr}
	, p_d3d_device_{nullptr}
	{

}

Core::~Core() {

}

//윈도우 닫히기 전 리소스 정리작업
int Core::OnDestroy() {
	SceneManager::GetInstance()->get_current_scene()->~Scene();
	
	if (p_d3d_device_ != NULL) p_d3d_device_->Release();
	if (p_d3d_ != NULL) p_d3d_->Release();

	//ReleaseDC(hwnd_, hdc_);
	//DeleteDC(hdc_mem_);
	//DeleteObject(hbitmap_);
	//pen과 brush 삭제
	for (int i = 0; i < static_cast<int>(PEN_TYPE::END); i++) DeleteObject(pens[i]);
	for (int i = 0; i < static_cast<int>(BRUSH_TYPE::END); i++) DeleteObject(brushes[i]);
	
	return S_OK;
}


int Core::Init(HWND h_wnd, int width, int height) {
	
	//메모리 누수 체크
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(8808);
	//_CrtSetBreakAlloc(1446);

	hwnd_ = h_wnd;
	hdc_ = GetDC(hwnd_);
	RECT rect{ 0, 0, width, height };
	pt_resolution_ = POINT{ rect.right - rect.left, rect.bottom - rect.top };

	if (!AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, TRUE)) {
		return E_FAIL;
	}
	if (!SetWindowPos(h_wnd, nullptr, 100, 100, rect.right - rect.left, rect.bottom - rect.top, 0)) {
		return E_FAIL;
	}
	
	
	//=================
	// Direct X 초기화
	//=================
	if (( p_d3d_ = Direct3DCreate9(D3D_SDK_VERSION) ) == NULL) {
		return E_FAIL;
	}

	D3DPRESENT_PARAMETERS d3d_params;
	ZeroMemory(&d3d_params, sizeof(d3d_params));
	d3d_params.Windowed = true;
	d3d_params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3d_params.BackBufferFormat = D3DFMT_UNKNOWN;
	//d3d_params.EnableAutoDepthStencil = TRUE;
	//d3d_params.AutoDepthStencilFormat = D3DFMT_D16;

	if(FAILED(p_d3d_->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd_, 
									D3DCREATE_MIXED_VERTEXPROCESSING, &d3d_params, 
									&p_d3d_device_)))
	{
		p_d3d_->Release();
		return E_FAIL;
	}

	
	

	/*hbitmap_ = CreateCompatibleBitmap(hdc_, pt_resolution_.x, pt_resolution_.y);
	hdc_mem_ = CreateCompatibleDC(hdc_);
	HBITMAP org_bitmap = (HBITMAP) SelectObject(hdc_mem_, hbitmap_);
	DeleteObject(org_bitmap);*/

	
	InitPenAndBrush();
	Time::GetInstance()->Init(h_wnd);
	KeyManager::GetInstance()->Init();
	PathManager::GetInstance()->Init();
	SceneManager::GetInstance()->Init( p_d3d_device_);
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
	Camera::GetInstance()->Update();

	//===============
	//	메인 루틴
	//===============
	SceneManager::GetInstance()->Update();
	
	//===============
	//	마무리 루틴
	//===============
	CollisionManager::GetInstance()->Update();
	UiManager::GetInstance()->FinalUpdate();

	//===============
	//	화면 렌더링
	//===============
	p_d3d_device_->BeginScene();
	SceneManager::GetInstance()->ClearView(p_d3d_device_);
	SceneManager::GetInstance()->Render(p_d3d_device_);
	p_d3d_device_->EndScene();
	p_d3d_device_->Present(0, 0, 0/*기본값:d3d_params의 멤버 hwnd*/, 0);
	//BitBlt(hdc_, 0, 0, pt_resolution_.x, pt_resolution_.y, hdc_mem_, 0, 0, SRCCOPY);


	//===============
	//	이벤트 지연 처리
	//===============
	EventManager::GetInstance()->Update();

	return TRUE;
}



void Core::SyncResolution()
{
	//해상도값과 실제 해상도값 비교(작업영역)
	RECT window_rect;
	GetWindowRect(hwnd_, &window_rect);
	RECT resolution_rect{ 0, 0, pt_resolution_.x, pt_resolution_.y };
	AdjustWindowRect(&resolution_rect, WS_OVERLAPPEDWINDOW, TRUE);

	
	if (resolution_rect.right - resolution_rect.left != window_rect.right - window_rect.left
		|| resolution_rect.bottom - resolution_rect.top != window_rect.bottom - window_rect.top) {
		LONG width_diff = (window_rect.right - window_rect.left) - (resolution_rect.right - resolution_rect.left);
		LONG height_diff = (window_rect.bottom - window_rect.top) - (resolution_rect.bottom - resolution_rect.top);
		pt_resolution_.x += width_diff;
		pt_resolution_.y += height_diff;

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
	pens[static_cast<int>(PEN_TYPE::BLACK_DASH)] = (HPEN)CreatePen(PS_DASH, 1, RGB(0, 0, 0));

	brushes[static_cast<int>(BRUSH_TYPE::BLACK)] = (HBRUSH)GetStockObject(BLACK_BRUSH);
	brushes[static_cast<int>(BRUSH_TYPE::WHITE)] = (HBRUSH)GetStockObject(WHITE_BRUSH);
	brushes[static_cast<int>(BRUSH_TYPE::BRIGHT_GRAY)] = (HBRUSH)CreateSolidBrush(RGB(200, 200, 200));
	brushes[static_cast<int>(BRUSH_TYPE::RED)] = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
	brushes[static_cast<int>(BRUSH_TYPE::GREEN)] = (HBRUSH)CreateSolidBrush(RGB(0, 255, 0));
	brushes[static_cast<int>(BRUSH_TYPE::BLUE)] = (HBRUSH)CreateSolidBrush(RGB(0, 0, 255));
	brushes[static_cast<int>(BRUSH_TYPE::HOLLOW)] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	brushes[static_cast<int>(BRUSH_TYPE::MAGENTA)] = (HBRUSH)CreateSolidBrush(RGB(255, 0, 255));
}

