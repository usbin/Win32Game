#include "Scene_Title.h"
#include "KeyManager.h"
#include "Time.h"
#include "Player.h"
#include "Monster.h"
#include "Core.h"
#include "Texture.h"
#include "CollisionManager.h"
#include "PanelUi.h"
#include "Camera.h"
#include "ButtonUi.h"
#include "ImageUi.h"
#include "GObjectSprite.h"
#include "Director_Scene_Title.h"
#include "Background_Title.h"
#include "TitleText_Title.h"
#include "NewGameBtn_Title.h"
bool Scene_Title::Enter(SCENE_TYPE from)
{
	Director_Scene_Title* dst = DEBUG_NEW Director_Scene_Title();
	dst->set_group_type(GROUP_TYPE::DIRECTOR);
	CreateGObject(dst, GROUP_TYPE::DIRECTOR);

	//==========================
	// 게임 배경, 시작 버튼 생성
	//===========================
	Background_Title* bg = DEBUG_NEW Background_Title();
	Vector2 bg_size = Core::GetInstance()->get_resolution();
	bg->set_pos(Vector2{ 0, 0 });
	bg->set_scale(bg_size);
	bg->set_group_type(GROUP_TYPE::UI);
	CreateGObject(bg, GROUP_TYPE::UI);


	TitleText_Title* title_text = DEBUG_NEW TitleText_Title();	
	//초기 위치 : 화면 밖
	Vector2 resolution = Core::GetInstance()->get_resolution();
	title_text->set_pos(Vector2(resolution.x, resolution.y / 5.f));
	title_text->set_scale(Vector2(resolution.x, 200.f));
	title_text->set_group_type(GROUP_TYPE::UI);
	CreateGObject(title_text, GROUP_TYPE::UI);

	NewGameBtn_Title* new_game_btn = DEBUG_NEW NewGameBtn_Title();
	Vector2 scale(150, 50);
	new_game_btn->set_pos(Vector2(resolution.x / 2.f - scale.x / 2.f, resolution.y * 2.f / 4.f));
	new_game_btn->set_scale(scale);
	new_game_btn->set_group_type(GROUP_TYPE::UI);
	new_game_btn->set_visible(false);
	new_game_btn->set_enabled(false);
	CreateGObject(new_game_btn, GROUP_TYPE::UI);
	
	new_game_btn->AddOnClickHandler([](DWORD_PTR _, DWORD_PTR __) {
		ChangeScene(SCENE_TYPE::SCENE_FARM);
		}, 0, 0);


	dst->Init(bg, title_text, new_game_btn);
	Camera::GetInstance()->unset_limit();

	return TRUE;
}


bool Scene_Title::Exit()
{
	Scene::DeleteAllObjects();

	Camera::GetInstance()->set_target(nullptr);
	return TRUE;
}
