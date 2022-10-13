#include "SceneManager.h"
#include "Scene_Title.h"
#include "Scene_01.h"
#include "Scene_Tool.h"
#include "KeyManager.h"
#include "Core.h"

SceneManager::SceneManager()
	: p_current_scene_(nullptr)
	, scenes_{}
	, hdc_{ 0 }
{
}

SceneManager::~SceneManager() {
	//모든 씬 삭제
	for (int i = 0; i < static_cast<int>(SCENE_TYPE::END); i++) {
		delete scenes_[i];
	}
}

bool SceneManager::Init(HDC hdc)
{
	hdc_ = hdc;
	//모든 씬 생성, 초기화
	scenes_[static_cast<int>(SCENE_TYPE::TITLE)] = new Scene_Title( hdc_ );
	scenes_[static_cast<int>(SCENE_TYPE::TITLE)]->set_name(_T("Scene Title"));
	scenes_[static_cast<int>(SCENE_TYPE::SCENE_01)] = new Scene_01{ hdc_ };
	scenes_[static_cast<int>(SCENE_TYPE::SCENE_01)]->set_name(_T("Scene 01"));
	scenes_[static_cast<int>(SCENE_TYPE::SCENE_TOOL)] = new Scene_Tool{ hdc_ };
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

bool SceneManager::Render(HDC hdc) {
	p_current_scene_->Render(hdc);
	return TRUE;
}
bool SceneManager::ChangeScene(SCENE_TYPE type)
{
	p_current_scene_->Exit();
	p_current_scene_ = scenes_[static_cast<int>(type)];
	p_current_scene_->Enter();
	return TRUE;
}
void SceneManager::ClearView(HDC hdc) {
	Rectangle(hdc, -1, -1, Core::GetInstance()->get_pt_resolution().x + 1, Core::GetInstance()->get_pt_resolution().y + 1);
}