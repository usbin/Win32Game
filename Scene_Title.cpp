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
#include "Sprite.h"
#include "Director_Scene_Title.h"

bool Scene_Title::Enter()
{
	Director_Scene_Title* dst = new Director_Scene_Title();
	dst->set_group_type(GROUP_TYPE::DIRECTOR);
	CreateGObject(dst, GROUP_TYPE::DIRECTOR);

	GObject* gobj = new Player();
	gobj->set_pos(Vector2{ 100, 100 });
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

	Ui* child_panel1 = new PanelUi();
	child_panel1->set_pos(Vector2{ 0, 0 });
	child_panel1->set_scale(Vector2{ 150, 50 });
	child_panel1->set_group_type(GROUP_TYPE::UI);
	child_panel1->set_parent(ui1);
	child_panel1->set_name(_T("child_ui1"));
	ui1->AddChild(child_panel1);

	ButtonUi* button_ui = new ButtonUi(true);
	button_ui->set_pos(Vector2{ 0, 0 });
	button_ui->set_scale(Vector2{ 40, 20 });
	button_ui->set_group_type(GROUP_TYPE::UI);
	button_ui->set_parent(child_panel1);
	button_ui->set_name(_T("button_ui"));
	child_panel1->AddChild(button_ui);
	button_ui->AddOnClickHandler([](DWORD_PTR param1, DWORD_PTR param2) {
		SetWindowText(Core::GetInstance()->get_main_hwnd(), _T("클릭함!"));
	}, 0, 0);

	Ui* child_panel2 = new PanelUi();
	child_panel2->set_pos(Vector2{ 150, 150 });
	child_panel2->set_scale(Vector2{ 50, 50 });
	child_panel2->set_group_type(GROUP_TYPE::UI);
	child_panel2->set_parent(ui1);
	child_panel2->set_name(_T("child_ui2"));
	ui1->AddChild(child_panel2);

	ImageUi* image_ui = new ImageUi(true);
	image_ui->set_pos(Vector2{ 50, 300 });
	image_ui->set_scale(Vector2{ 100, 100 });
	image_ui->set_group_type(GROUP_TYPE::UI);
	image_ui->set_parent(ui1);
	image_ui->set_name(_T("image_ui"));
	Texture* texture = ResManager::GetInstance()->LoadTexture(_T("Image Background"), _T("texture\\sample.bmp"));
	Sprite* sprite = new Sprite();
	sprite->QuickSet(texture, image_ui, 0, 0, 1, 1);
	image_ui->ChangeSprite(sprite);
	ui1->AddChild(image_ui);

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

	Camera::GetInstance()->set_target(nullptr);
	return TRUE;
}
