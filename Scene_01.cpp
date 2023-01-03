#include "Scene_01.h"
#include "KeyManager.h"
#include "Time.h"
#include "Player.h"
#include "CollisionManager.h"
#include "TimerUi.h"
#include "ResManager.h"
#include "RealObjectSprite.h"
#include "Monster.h"
#include "Game.h"
#include "Director_Scene_01.h"
bool Scene_01::Enter()
{
	Director_Scene_01* director = DEBUG_NEW Director_Scene_01();
	director->set_group_type(GROUP_TYPE::DIRECTOR);
	CreateGObject(director, GROUP_TYPE::DIRECTOR);


	GObject* gobj = DEBUG_NEW Player();
	gobj->set_pos(Vector2{ 500, 500 });
	gobj->set_group_type(GROUP_TYPE::PLAYER);
	CreateGObject(gobj, GROUP_TYPE::PLAYER);

	TimerUi* timer_ui = DEBUG_NEW TimerUi();
	timer_ui->set_pos(Vector2(0, 0));
	timer_ui->set_scale(Vector2(200, 100));
	timer_ui->set_group_type(GROUP_TYPE::UI);
	CreateGObject(timer_ui, GROUP_TYPE::UI);
	Texture* texture = ResManager::GetInstance()->LoadTexture(_T("Ingame Timer Ui Background"), _T("texture\\black.png"));
	Sprite* sprite = DEBUG_NEW RealObjectSprite();
	sprite->QuickSet(texture, timer_ui, timer_ui->get_pos(), timer_ui->get_scale());
	timer_ui->ChangeSprite(sprite);
	
	Monster* monster = DEBUG_NEW Monster();
	monster->set_pos(Vector2{ 600, 500 });
	monster->set_center_pos(Vector2{ 600, 500 });
	monster->set_move_range(0.0);
	monster->set_move_speed(0.5f);
	monster->set_scale(Vector2{ 50, 50 });
	

	monster->set_group_type(GROUP_TYPE::MONSTER);
	CreateGObject(monster, GROUP_TYPE::MONSTER);
		

	//자식 항목 만들기
	Game::GetInstance()->StartGame();
	return TRUE;
}


bool Scene_01::Exit()
{
	Scene::DeleteAllObjects();
	return TRUE;
}
