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
#include "BottomInventoryUi.h"
#include "Core.h"
#include "Camera.h"
#include "FileManager.h"
#include "PathManager.h"
bool Scene_01::Enter()
{
	Camera::GetInstance()->set_look_pos(Vector2{ 0, 0 });

	Director_Scene_01* director = DEBUG_NEW Director_Scene_01();
	director->set_group_type(GROUP_TYPE::DIRECTOR);
	CreateGObject(director, GROUP_TYPE::DIRECTOR);

	Player* player = DEBUG_NEW Player();
	player->set_pos(Vector2{ 500, 500 });
	player->set_group_type(GROUP_TYPE::PLAYER);
	CreateGObject(player, GROUP_TYPE::PLAYER);

	TimerUi* timer_ui = DEBUG_NEW TimerUi();
	timer_ui->set_pos(Vector2(0, 0));
	timer_ui->set_scale(Vector2(200, 100));
	timer_ui->set_group_type(GROUP_TYPE::UI);
	CreateGObject(timer_ui, GROUP_TYPE::UI);

	Texture* texture = ResManager::GetInstance()->LoadTexture(_T("TimerUi_Background"), _T("texture\\light-gray.png"));
	GObjectSprite* sprite = DEBUG_NEW RealObjectSprite();
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
	
	
	BottomInventoryUi* inventory_ui = DEBUG_NEW BottomInventoryUi();
	Vector2 resolution = Core::GetInstance()->get_resolution();
	inventory_ui->set_scale(Vector2{ resolution.x * 0.7f, 60.f });
	inventory_ui->set_pos(Vector2{ resolution.x * 0.15f, resolution.y - 60.f });
	inventory_ui->set_group_type(GROUP_TYPE::UI);
	inventory_ui->Init(player);
	inventory_ui->CreateEmptyCells();
	CreateGObject(inventory_ui, GROUP_TYPE::UI);


	FileManager::GetInstance()->LoadMap(PathManager::GetInstance()->GetContentPath()+_T("map\\Farm_NoWall.map"));


	Camera::GetInstance()->set_target(player);
	//자식 항목 만들기
	Game::GetInstance()->StartGame();
	return TRUE;
}


bool Scene_01::Exit()
{
	Scene::DeleteAllObjects();
	return TRUE;
}
