#include "Scene_Tool.h"
#include "Director_Scene_Tool.h"
#include "SceneManager.h"
#include "Player.h"
#include "Camera.h"
#include "TileUi.h"
#include "ResManager.h"
#include "Sprite.h"
#include "CollisionManager.h"
#include "Core.h"
Scene_Tool::Scene_Tool()
	:hdc_(0)
{
}

Scene_Tool::Scene_Tool(ID3D11Device* p_d3d_device)
	: Scene(p_d3d_device)
{
}


Scene_Tool::~Scene_Tool()
{
	
}

bool Scene_Tool::Enter()
{
	CollisionManager::GetInstance()->CheckGroupBitmap(GROUP_TYPE::PLAYER, GROUP_TYPE::INVISIBLE_WALL);

	Director_Scene_Tool* dst = new Director_Scene_Tool();
	dst->set_group_type(GROUP_TYPE::DIRECTOR);
	CreateGObject(dst, GROUP_TYPE::DIRECTOR);


	//화면에 기본 1024x1024 빈 타일맵 만들기
	SceneManager::GetInstance()->get_current_scene()->CreateTile(10, 10);
	

	GObject* gobj = new Player();
	gobj->set_pos(Vector2{ 0, 0 });
	gobj->set_scale(Vector2{ 50, 50 });
	gobj->set_group_type(GROUP_TYPE::PLAYER);
	CreateGObject(gobj, GROUP_TYPE::PLAYER);

	//글씨 쓰기 테스트 코드
	ButtonUi* draw_text_btn = new ButtonUi(true);
	draw_text_btn->set_pos(Vector2(0, 100));
	draw_text_btn->set_scale(Vector2(200, 100));
	draw_text_btn->set_group_type(GROUP_TYPE::UI);
	draw_text_btn->AddOnClickHandler([](DWORD_PTR param1, DWORD_PTR param2) {
		//클릭했을 때 동작

		}, 0, 0);
	CreateGObject(draw_text_btn, GROUP_TYPE::UI);




	//Camera::GetInstance()->set_target(gobj);
	return true;
}

bool Scene_Tool::Exit()
{
	SceneManager::GetInstance()->get_current_scene()->DeleteAllObjects();
	return true;
}
