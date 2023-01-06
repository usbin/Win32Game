#include "SceneManager.h"
#include "Scene_Title.h"
#include "Scene_01.h"
#include "Scene_Tool.h"
#include "KeyManager.h"
#include "DXClass.h"

SceneManager::SceneManager()
	: p_current_scene_(nullptr)
	, scenes_{}
	, hdc_{ 0 }
{
	memset(scenes_, 0, sizeof(scenes_));
}

SceneManager::~SceneManager() {
	//모든 씬 삭제
	for (int i = 0; i < static_cast<int>(SCENE_TYPE::END); i++) {
		delete scenes_[i];
	}
}

bool SceneManager::Init(ID3D11Device* p_d3d_device)
{
//	hdc_ = hdc;
//	//모든 씬 생성, 초기화
//	scenes_[static_cast<int>(SCENE_TYPE::TITLE)] = new Scene_Title( hdc_ );
//	scenes_[static_cast<int>(SCENE_TYPE::TITLE)]->set_name(_T("Scene Title"));
//	scenes_[static_cast<int>(SCENE_TYPE::SCENE_01)] = new Scene_01{ hdc_ };
//	scenes_[static_cast<int>(SCENE_TYPE::SCENE_01)]->set_name(_T("Scene 01"));
//	scenes_[static_cast<int>(SCENE_TYPE::SCENE_TOOL)] = new Scene_Tool{ hdc_ };
//	scenes_[static_cast<int>(SCENE_TYPE::SCENE_TOOL)]->set_name(_T("Scene Tool"));
//
//
//	//시작 씬 설정
//	p_current_scene_ = scenes_[static_cast<int>(SCENE_TYPE::TITLE)];
//	p_current_scene_->Enter();

	p_d3d_device_ = p_d3d_device;
	//모든 씬 생성, 초기화
	scenes_[static_cast<int>(SCENE_TYPE::TITLE)] = DEBUG_NEW Scene_Title(p_d3d_device_);
	scenes_[static_cast<int>(SCENE_TYPE::TITLE)]->set_name(_T("Scene Title"));
	scenes_[static_cast<int>(SCENE_TYPE::SCENE_01)] = DEBUG_NEW Scene_01{ p_d3d_device_ };
	scenes_[static_cast<int>(SCENE_TYPE::SCENE_01)]->set_name(_T("Scene 01"));
	scenes_[static_cast<int>(SCENE_TYPE::SCENE_TOOL)] = DEBUG_NEW Scene_Tool{ p_d3d_device_ };
	scenes_[static_cast<int>(SCENE_TYPE::SCENE_TOOL)]->set_name(_T("Scene Tool"));


	//시작 씬 설정
	p_current_scene_ = scenes_[static_cast<int>(SCENE_TYPE::TITLE)];
	p_current_scene_->Enter();

	return TRUE;
}


bool SceneManager::Update() {
	p_current_scene_->Update();
	return TRUE;
}

bool SceneManager::Render(ID3D11Device* p_d3d_device) {
	p_current_scene_->Render(p_d3d_device);
	return TRUE;
}
bool SceneManager::ChangeScene(SCENE_TYPE type)
{
	p_current_scene_->Exit();
	p_current_scene_ = scenes_[static_cast<int>(type)];
	p_current_scene_->Enter();
	return TRUE;
}
void SceneManager::ClearView(ID3D11Device* p_d3d_device) {
	ID3D11DeviceContext* context;
	p_d3d_device->GetImmediateContext(&context);
	float ClearColor[4] = { 1.0f, 1.0f, 1.0f, 0.0f };
	context->ClearRenderTargetView(DXClass::GetInstance()->get_render_target_view(), ClearColor);
	context->ClearDepthStencilView(DXClass::GetInstance()->get_depth_view(), D3D11_CLEAR_DEPTH, 1.f, 0);
	context->Release();
}