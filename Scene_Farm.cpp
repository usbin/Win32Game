#include "Scene_Farm.h"
#include "KeyManager.h"
#include "Time.h"
#include "Player.h"
#include "CollisionManager.h"
#include "TimerUi.h"
#include "ResManager.h"
#include "RealObjectSprite.h"
#include "Monster.h"
#include "Game.h"
#include "Director_Scene_Farm.h"
#include "BottomInventoryUi.h"
#include "Core.h"
#include "Camera.h"
#include "FileManager.h"
#include "PathManager.h"
#include "TileObject.h"
#include "ShippingBox.h"
#include "RuntimeData.h"
#include "FarmhouseDoor.h"
#include "UiSprite.h"
bool Scene_Farm::Enter(SCENE_TYPE from)
{
	if (!initialized_) {
		//이 맵에 들어오면 1번에 한해 초기화
		Initialize();
	}
	else {
		//이미 초기화 된 후면 활성화+플레이어 데이터 동기화만
		Reinitialize(from);
	}
	
	return TRUE;
}


bool Scene_Farm::Exit()
{
	DeleteGroupObjects(GROUP_TYPE::UI);
	Scene::DisableAllObjects();

	std::vector<GObject*> gobjs = GetGroupObjects(GROUP_TYPE::PLAYER);
	if (!gobjs.empty()) {
		RuntimeData::GetInstance()->SavePlayerData(dynamic_cast<Player*>(gobjs[0]));
	}

	return TRUE;
}

void Scene_Farm::Initialize()
{
	// 맵 로드
	FileManager::GetInstance()->LoadMap(PathManager::GetInstance()->GetContentPath() + _T("map\\Farm.map"));
	// 카메라 설정
	Camera::GetInstance()->set_look_pos(Vector2{ 0, 0 }	);

	//디렉터 생성
	Director_Scene_Farm* director = DEBUG_NEW Director_Scene_Farm();
	director->set_group_type(GROUP_TYPE::DIRECTOR);
	CreateGObject(director, GROUP_TYPE::DIRECTOR);

	//플레이어 생성
	Player* player = DEBUG_NEW Player();
	player->set_pos(Vector2{ 3096, 958 });
	player->set_group_type(GROUP_TYPE::PLAYER);
	CreateGObject(player, GROUP_TYPE::PLAYER);

	//출하상자 생성
	ShippingBox* shipping_box = DEBUG_NEW ShippingBox();
	shipping_box->set_pos(Vector2{ 3457, 718 });
	shipping_box->set_scale(Vector2{ 96, 96 });
	shipping_box->set_group_type(GROUP_TYPE::SHIPPING_BOX);
	shipping_box->Init();
	CreateGObject(shipping_box, GROUP_TYPE::SHIPPING_BOX);

	//집 문 생성
	FarmhouseDoor* door = DEBUG_NEW FarmhouseDoor();
	door->set_pos(Vector2{ 3095, 695 });
	door->set_scale(Vector2{ 48, 48 });
	door->set_name(_T("집 문"));
	door->set_group_type(GROUP_TYPE::THING);
	door->Init();
	CreateGObject(door, GROUP_TYPE::THING);
	

	//============================
	// UI 생성
	//============================
	CreateUis(player);

	Camera::GetInstance()->set_target(player);
	Camera::GetInstance()->set_limit(Vector2::Zero(), Vector2{ 3835, 3113 });
	Game::GetInstance()->StartGame();
	
	initialized_ = true;
}

void Scene_Farm::Reinitialize(SCENE_TYPE from)
{
	EnableAllObjects();
	std::vector<GObject*> gobjs = GetGroupObjects(GROUP_TYPE::PLAYER);
	if (!gobjs.empty()) {
		Player* player = dynamic_cast<Player*>(gobjs[0]);
		RuntimeData::GetInstance()->LoadPlayerData(player);
		player->set_enabled(true);
		Camera::GetInstance()->set_target(player);

		//집에서 나온 거면 위치를 집 문앞으로.
		if (from == SCENE_TYPE::SCENE_FARMHOUSE) {
			player->set_pos(Vector2{ 3095, 725 });
		}
		Camera::GetInstance()->set_limit(Vector2::Zero(), Vector2{ 3835, 3113 });

		//============================
		// UI 생성
		//============================
		CreateUis(player);
	}

	
}

void Scene_Farm::CreateUis(Player* player)
{
	TimerUi* timer_ui = DEBUG_NEW TimerUi();
	timer_ui->Init(player);
	timer_ui->set_group_type(GROUP_TYPE::UI);
	CreateGObject(timer_ui, GROUP_TYPE::UI);

	BottomInventoryUi* inventory_ui = DEBUG_NEW BottomInventoryUi();
	Vector2 resolution = Core::GetInstance()->get_resolution();
	inventory_ui->set_group_type(GROUP_TYPE::UI);
	inventory_ui->Init(player);
	CreateGObject(inventory_ui, GROUP_TYPE::UI);
}
