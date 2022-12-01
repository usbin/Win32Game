#include "Core.h"
#include "Time.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "PathManager.h"
#include "CollisionManager.h"
#include "EventManager.h"
#include "Camera.h"
#include "UiManager.h"
#include "DXClass.h"

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

//������ ������ �� ���ҽ� �����۾�
int Core::OnDestroy() {
	SceneManager::GetInstance()->get_current_scene()->~Scene();
	
	

	//pen�� brush ����
	for (int i = 0; i < static_cast<int>(PEN_TYPE::END); i++) DeleteObject(pens[i]);
	for (int i = 0; i < static_cast<int>(BRUSH_TYPE::END); i++) DeleteObject(brushes[i]);
	
	return S_OK;
}


int Core::Init(HWND h_wnd, int width, int height) {

	//==============
	// ������ �ʱ�ȭ
	//==============

	//�޸� ���� üũ
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
	// ���� �ʱ�ȭ �۾�
	//=================

	InitPenAndBrush();
	Time::GetInstance()->Init(h_wnd);
	KeyManager::GetInstance()->Init();
	PathManager::GetInstance()->Init();

	//=================
	// Direct X �ʱ�ȭ
	//=================
	if (FAILED(DXClass::GetInstance()->Init(h_wnd, Vector2(pt_resolution_)))) {
		return E_FAIL;
	}

	//================
	// ���� �ʱ�ȭ �۾�
	//=================
	SceneManager::GetInstance()->Init(DXClass::GetInstance()->get_d3d_device());
	CollisionManager::GetInstance()->Init();

	return S_OK;
}





bool Core::Progress()
{
	//===============
	//	�����۾�
	//===============
	SyncResolution();
	Time::GetInstance()->Update();
	KeyManager::GetInstance()->Update();
	Camera::GetInstance()->Update();

	//===============
	//	���� ��ƾ
	//===============
	SceneManager::GetInstance()->Update();
	
	//===============
	//	������ ��ƾ
	//===============
	CollisionManager::GetInstance()->Update();
	UiManager::GetInstance()->FinalUpdate();

	//===============
	//	ȭ�� ������
	//===============
	SceneManager::GetInstance()->ClearView(DXClass::GetInstance()->get_d3d_device());
	SceneManager::GetInstance()->Render(DXClass::GetInstance()->get_d3d_device());
	
	DXClass::GetInstance()->get_swap_chain()->Present(0, 0);
	//BitBlt(hdc_, 0, 0, pt_resolution_.x, pt_resolution_.y, hdc_mem_, 0, 0, SRCCOPY);


	//===============
	//	�̺�Ʈ ���� ó��
	//===============
	EventManager::GetInstance()->Update();

	return TRUE;
}



void Core::SyncResolution()
{
	//�ػ󵵰��� ���� �ػ󵵰� ��(�۾�����)
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



		//�Ķ���� ���ۿ� �ػ� �Է�
		//Constant Buffer ����
		DXClass::GetInstance()->WriteConstantBufferOnResize(pt_resolution_);

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

