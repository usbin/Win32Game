#include "SceneManager.h"
#include "Scene_Title.h"
#include "Scene_Farm.h"
#include "Scene_Farmhouse.h"
#include "Scene_Tool.h"
#include "KeyManager.h"
#include "DXClass.h"
#include "EventManager.h"
#include "Core.h"
SceneManager::SceneManager()
	: p_current_scene_(nullptr)
	, scenes_{}
	, hdc_{ 0 }
{
	memset(scenes_, 0, sizeof(scenes_));
}

SceneManager::~SceneManager() {
	//��� �� ����
	for (int i = 0; i < static_cast<int>(SCENE_TYPE::END); i++) {
		delete scenes_[i];
		scenes_[i] = nullptr;
	}
}

bool SceneManager::Init(ID3D11Device* p_d3d_device)
{
//	hdc_ = hdc;
//	//��� �� ����, �ʱ�ȭ
//	scenes_[static_cast<int>(SCENE_TYPE::TITLE)] = new Scene_Title( hdc_ );
//	scenes_[static_cast<int>(SCENE_TYPE::TITLE)]->set_name(_T("Scene Title"));
//	scenes_[static_cast<int>(SCENE_TYPE::SCENE_01)] = new Scene_01{ hdc_ };
//	scenes_[static_cast<int>(SCENE_TYPE::SCENE_01)]->set_name(_T("Scene 01"));
//	scenes_[static_cast<int>(SCENE_TYPE::SCENE_TOOL)] = new Scene_Tool{ hdc_ };
//	scenes_[static_cast<int>(SCENE_TYPE::SCENE_TOOL)]->set_name(_T("Scene Tool"));
//
//
//	//���� �� ����
//	p_current_scene_ = scenes_[static_cast<int>(SCENE_TYPE::TITLE)];
//	p_current_scene_->Enter();

	p_d3d_device_ = p_d3d_device;
	//��� �� ����, �ʱ�ȭ
	scenes_[static_cast<int>(SCENE_TYPE::TITLE)] = DEBUG_NEW Scene_Title(p_d3d_device_);
	scenes_[static_cast<int>(SCENE_TYPE::TITLE)]->set_name(_T("Scene Title"));
	scenes_[static_cast<int>(SCENE_TYPE::SCENE_FARM)] = DEBUG_NEW Scene_Farm{ p_d3d_device_ };
	scenes_[static_cast<int>(SCENE_TYPE::SCENE_FARM)]->set_name(_T("Scene Farm"));
	scenes_[static_cast<int>(SCENE_TYPE::SCENE_FARMHOUSE)] = DEBUG_NEW Scene_Farmhouse{ p_d3d_device_ };
	scenes_[static_cast<int>(SCENE_TYPE::SCENE_FARMHOUSE)]->set_name(_T("Scene Farmhouse"));
	scenes_[static_cast<int>(SCENE_TYPE::SCENE_TOOL)] = DEBUG_NEW Scene_Tool{ p_d3d_device_ };
	scenes_[static_cast<int>(SCENE_TYPE::SCENE_TOOL)]->set_name(_T("Scene Tool"));


	//���� �� ����
	p_current_scene_ = scenes_[static_cast<int>(SCENE_TYPE::TITLE)];
	p_current_scene_->Enter(SCENE_TYPE::END);

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
bool SceneManager::ChangeSceneExit()
{
	p_current_scene_->Exit();
	Game::GetInstance()->ShowLoading();
	return TRUE;
}

bool SceneManager::ChangeSceneEnter(SCENE_TYPE type)
{
	p_current_scene_ = scenes_[static_cast<int>(type)];
	p_current_scene_->Enter(current_scene_type_);
	current_scene_type_ = type;
	Game::GetInstance()->UnshowLoading();
	return true;
}

void SceneManager::ClearView(ID3D11Device* p_d3d_device) {
	ID3D11DeviceContext* context;
	p_d3d_device->GetImmediateContext(&context);
	float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	context->ClearRenderTargetView(DXClass::GetInstance()->get_render_target_view(), ClearColor);
	for (int i = 0; i < (int)RENDER_LAYER::END; i++) {
		context->ClearRenderTargetView(DXClass::GetInstance()->get_render_layer_target((RENDER_LAYER)i), ClearColor);
		DXClass::GetInstance()->get_text_bitmap((RENDER_LAYER)i)->BeginDraw();
		DXClass::GetInstance()->get_text_bitmap((RENDER_LAYER)i)->Clear();
		DXClass::GetInstance()->get_text_bitmap((RENDER_LAYER)i)->EndDraw();
	}



	context->Release();
}

const std::vector<GObject*> SceneManager::GetAllShippingBoxes()
{
	std::vector<GObject*> shipping_boxes;
	for (int i = 0; i < (int)SCENE_TYPE::END; i++) {
		std::vector<GObject*> gobjs = scenes_[i]->GetGroupObjects(GROUP_TYPE::SHIPPING_BOX);
		shipping_boxes.insert(shipping_boxes.end(), gobjs.begin(), gobjs.end());
	}
	return shipping_boxes;
}
