#include "Scene_Tool.h"
#include "Director_Scene_Tool.h"
#include "SceneManager.h"
#include "Player.h"
#include "Camera.h"
#include "TileUi.h"
#include "ResManager.h"
#include "Sprite.h"
Scene_Tool::Scene_Tool()
	:hdc_(0)
{
}

Scene_Tool::Scene_Tool(HDC hdc)
	: hdc_(hdc)
{
}


Scene_Tool::~Scene_Tool()
{
}

bool Scene_Tool::Enter()
{
	Director_Scene_Tool* dst = new Director_Scene_Tool();
	dst->set_group_type(GROUP_TYPE::DIRECTOR);
	CreateGObject(dst, GROUP_TYPE::DIRECTOR);


	//화면에 기본 1024x1024 빈 타일맵 만들기
	dst->CreateEmptyTilemap(Vector2{50, 50}, Vector2{ 1024/50, 1024/50 });
	

	GObject* gobj = new Player();
	gobj->set_pos(Vector2{ 100, 100 });
	gobj->set_scale(Vector2{ 50, 50 });
	gobj->set_group_type(GROUP_TYPE::PLAYER);
	CreateGObject(gobj, GROUP_TYPE::PLAYER);

	

	//Camera::GetInstance()->set_target(gobj);
	return true;
}

bool Scene_Tool::Exit()
{
	SceneManager::GetInstance()->get_current_scene()->DeleteAllObjects();
	return true;
}
