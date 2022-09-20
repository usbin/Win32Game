#include "pch.h"
#include "Scene_01.h"
#include "KeyManager.h"
#include "Time.h"
#include "Player.h"
#include "CollisionManager.h"

bool Scene_01::Enter()
{
	GObject* gobj = new Player();
	gobj->set_pos(Vector2{ 500, 500 });
	gobj->set_scale(Vector2{ 50, 50 });
	gobj->set_group_type(GROUP_TYPE::PLAYER);
	CreateGObject(gobj, GROUP_TYPE::PLAYER);
	return TRUE;
}


bool Scene_01::Exit()
{
	Scene::DeleteAllObjects();
	return TRUE;
}
