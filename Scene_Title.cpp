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
#include "UiSprite.h"
#include "ExitBtn_Title.h"
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
	title_text->set_pos(Vector2(resolution.x, resolution.y / 7.f));
	title_text->set_scale(Vector2(resolution.x/2.f, resolution.x*(104.f/228.f)/2.f));
	title_text->set_group_type(GROUP_TYPE::UI);
	Texture* texture = ResManager::GetInstance()->LoadTexture(_T("Stardew Valley Title Text"), _T("texture\\StardewValley_TitleText.png"));
	UiSprite* title_text_sprite = DEBUG_NEW UiSprite();
	title_text_sprite->QuickSet(texture, title_text, Vector2{ 0, 0 }, texture->get_size());
	title_text->ChangeSprite(title_text_sprite);
	CreateGObject(title_text, GROUP_TYPE::UI);

	NewGameBtn_Title* new_game_btn = DEBUG_NEW NewGameBtn_Title();
	Vector2 scale(170, 150);
	new_game_btn->set_pos(Vector2(resolution.x / 2.f - scale.x - 15.f, resolution.y * 3.f / 4.f));
	new_game_btn->set_scale(scale);
	new_game_btn->set_group_type(GROUP_TYPE::UI);
	new_game_btn->set_visible(false);
	new_game_btn->set_enabled(false);
	CreateGObject(new_game_btn, GROUP_TYPE::UI);

	ExitBtn_Title* exit_btn = DEBUG_NEW ExitBtn_Title(true);
	exit_btn->set_pos(Vector2(resolution.x / 2.f + 15.f, resolution.y * 3.f / 4.f));
	exit_btn->set_scale(scale);
	exit_btn->set_group_type(GROUP_TYPE::UI);
	exit_btn->set_visible(false);
	exit_btn->set_enabled(false);
	CreateGObject(exit_btn, GROUP_TYPE::UI);
	
	new_game_btn->AddOnClickHandler([](DWORD_PTR _, DWORD_PTR __) {
		ChangeScene(SCENE_TYPE::SCENE_FARM);
		}, 0, 0);

	exit_btn->AddOnClickHandler([](DWORD_PTR _, DWORD_PTR __) {
		DestroyWindow(Core::GetInstance()->get_main_hwnd());
		}, 0, 0);

	dst->Init(bg, title_text, new_game_btn, exit_btn);
	Camera::GetInstance()->unset_limit();

	return TRUE;
}


bool Scene_Title::Exit()
{
	Scene::DeleteAllObjects();

	Camera::GetInstance()->set_target(nullptr);
	return TRUE;
}
