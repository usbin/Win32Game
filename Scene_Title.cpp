#include "Scene_Title.h"
#include "KeyManager.h"
#include "Time.h"
#include "Player.h"
#include "Monster.h"
#include "Core.h"
#include "Texture.h"
#include "CollisionManager.h"

bool Scene_Title::Enter()
{
	

	GObject* gobj = new Player();
	gobj->set_pos(Vector2{ 500, 500 });
	gobj->set_scale(Vector2{ 50, 50 });
	gobj->set_group_type(GROUP_TYPE::PLAYER);
	CreateGObject(gobj, GROUP_TYPE::PLAYER);



	int move_r = 50;
	int term = 150;
	int pos_y = 300;
	//좌측 끝+이동범위 부터 우측 끝-이동범위 까지 몬스터 생성
	for (int pos_x = move_r+25;
		pos_x < Core::GetInstance()->get_pt_resolution().x - move_r - 25; pos_x += term) {
		Monster* monster = new Monster();
		monster->set_pos(Vector2{ pos_x, pos_y });
		monster->set_scale(Vector2{ 50, 50 });
		monster->set_group_type(GROUP_TYPE::MONSTER);
		monster->set_center_pos(Vector2{ pos_x, pos_y });
		monster->set_move_range(static_cast<float>(move_r));
		CreateGObject(monster, GROUP_TYPE::MONSTER);
	}
	return TRUE;
}


bool Scene_Title::Exit()
{
	Scene::DeleteAllObjects();
	return TRUE;
}
