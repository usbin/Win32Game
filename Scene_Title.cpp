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

bool Scene_Title::Enter()
{
	

	GObject* gobj = new Player();
	gobj->set_pos(Vector2{ 500, 500 });
	gobj->set_scale(Vector2{ 50, 50 });
	gobj->set_group_type(GROUP_TYPE::PLAYER);
	CreateGObject(gobj, GROUP_TYPE::PLAYER);

	Ui* ui1 = new PanelUi();
	ui1->set_pos(Vector2{ 0, 0 });
	ui1->set_scale(Vector2{ 200, 400 });
	ui1->set_group_type(GROUP_TYPE::UI);
	ui1->set_name(_T("UI1"));
	CreateGObject(ui1, GROUP_TYPE::UI);

	Ui* ui2 = new PanelUi();
	ui2->set_pos(Vector2{ 0, 0 });
	ui2->set_scale(Vector2{ 200, 400 });
	ui2->set_group_type(GROUP_TYPE::UI);
	ui2->set_name(_T("UI2"));
	CreateGObject(ui2, GROUP_TYPE::UI);

	Ui* child_ui1 = new PanelUi();
	child_ui1->set_pos(Vector2{ 10, 10 });
	child_ui1->set_scale(Vector2{ 50, 50 });
	child_ui1->set_group_type(GROUP_TYPE::UI);
	child_ui1->set_parent(ui1);
	child_ui1->set_name(_T("child_ui1"));
	ui1->AddChild(child_ui1);

	Ui* child_ui2 = new PanelUi();
	child_ui2->set_pos(Vector2{ 450, 0 });
	child_ui2->set_scale(Vector2{ 50, 50 });
	child_ui2->set_group_type(GROUP_TYPE::UI);
	child_ui2->set_parent(ui1);
	child_ui2->set_name(_T("child_ui2"));
	ui1->AddChild(child_ui2);

	Camera::GetInstance()->set_target(gobj);

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
