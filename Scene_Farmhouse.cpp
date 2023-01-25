#include "Scene_Farmhouse.h"
#include "FileManager.h"
#include "PathManager.h"
#include "Camera.h"
#include "RuntimeData.h"
#include "FarmhouseDoor_Exit.h"
#include "FarmhouseBed.h"
#include "TimerUi.h"
#include "BottomInventoryUi.h"
#include "ResManager.h"
#include "UiSprite.h"
#include "Core.h"
#include "FmodSound.h"
bool Scene_Farmhouse::Enter(SCENE_TYPE from)
{
	if (!initialized_) {
		Initialize();
	}
	else {
		Reinitialize();
	}
	if (Game::GetInstance()->get_day_uptime_s() / 60 / 60 < 18) {
		Sound* ambience = ResManager::GetInstance()->LoadSound(_T("Farm Ambience"), _T("sound\\Farm_SpringDay_Bgm.wav"));
		FmodSound::GetInstance()->PlayAmbience(ambience);
	}
	else {
		Sound* ambience = ResManager::GetInstance()->LoadSound(_T("Farm Ambience"), _T("sound\\Farm_SpringNight_Bgm.wav"));
		FmodSound::GetInstance()->PlayAmbience(ambience);
	}
	Sound* sound = ResManager::GetInstance()->LoadSound(_T("DoorClose_Effect"), _T("sound\\DoorClose_Effect.wav"));
	FmodSound::GetInstance()->Play(FmodSound::GetInstance()->GetChannel(), sound, false);

	return true;
}

bool Scene_Farmhouse::Exit()
{
	DeleteGroupObjects(GROUP_TYPE::UI);
	Scene::DisableAllObjects();

	std::vector<GObject*> gobjs = GetGroupObjects(GROUP_TYPE::PLAYER);
	if (!gobjs.empty()) {
		RuntimeData::GetInstance()->SavePlayerData(dynamic_cast<Player*>(gobjs[0]));
	}

	FmodSound::GetInstance()->StopAmbience();
	return true;
}

void Scene_Farmhouse::Initialize()
{
	// �� �ε�
	FileManager::GetInstance()->LoadMap(PathManager::GetInstance()->GetContentPath() + _T("map\\Farmhouse.map"));
	// ī�޶� ����
	
	//ħ�� ����(������ "���ڱ�" ����)
	FarmhouseBed* bed = DEBUG_NEW FarmhouseBed();
	bed->set_pos(Vector2{ 526, 441 });
	bed->set_scale(Vector2{ 48, 48 });
	bed->set_name(_T("ħ��"));
	bed->set_group_type(GROUP_TYPE::THING);
	bed->Init();
	CreateGObject(bed, GROUP_TYPE::THING);


	//�� ����(������ Farm������ ������)
	FarmhouseDoor_Exit* door = DEBUG_NEW FarmhouseDoor_Exit();
	door->set_pos(Vector2{ 166, 585 });
	door->set_scale(Vector2{ 48, 48 });
	door->set_name(_T("�� ��"));
	door->set_group_type(GROUP_TYPE::THING);
	door->Init();
	CreateGObject(door, GROUP_TYPE::THING);

	//�÷��̾� ����
	Player* player = nullptr;
	std::vector<GObject*> gobjs = GetGroupObjects(GROUP_TYPE::PLAYER);
	if (!gobjs.empty()) {
		// CASE1 : ���� ���� player�� �̹� ���� => ����� �����͸� �ҷ���.
		player = dynamic_cast<Player*>(gobjs[0]);
		RuntimeData::GetInstance()->LoadPlayerData(player);
		player->set_enabled(true);
	}
	else {
		//CASE2 : player�� �������� ����. => �����ϰ� ����� �����͸� �ҷ���.
		player = DEBUG_NEW Player();

		RuntimeData::GetInstance()->LoadPlayerData(player);
		player->set_group_type(GROUP_TYPE::PLAYER);
		CreateGObject(player, GROUP_TYPE::PLAYER);
		player->set_pos(Vector2{ 173, 470 });
		player->set_direction(DIRECTION::UP);
		player->set_enabled(true);
	}
	CreateUis(player);
	Camera::GetInstance()->set_limit(Vector2{ 35, 0 }, Vector2{ 542, 540 });
	Camera::GetInstance()->set_look_pos(Vector2{ 300, 400 });
	Camera::GetInstance()->set_target(player);
	initialized_ = true;
}

void Scene_Farmhouse::Reinitialize()
{
	EnableAllObjects();
	//�÷��̾� ������ ����ȭ
	std::vector<GObject*> gobjs = GetGroupObjects(GROUP_TYPE::PLAYER);
	if (!gobjs.empty()) {
		Player* player = dynamic_cast<Player*>(gobjs[0]);
		RuntimeData::GetInstance()->LoadPlayerData(player);
		player->set_enabled(true);
		player->set_pos(Vector2{ 173, 470 });
		player->set_direction(DIRECTION::UP);
		Camera::GetInstance()->set_limit(Vector2{ 35, 0 }, Vector2{ 542, 540 });
		Camera::GetInstance()->set_look_pos(Vector2{ 300, 400 });
		Camera::GetInstance()->set_target(player);
		CreateUis(player);
	}
}

void Scene_Farmhouse::CreateUis(Player* player)
{
	TimerUi* timer_ui = DEBUG_NEW TimerUi();
	timer_ui->set_group_type(GROUP_TYPE::UI);
	timer_ui->Init(player);
	CreateGObject(timer_ui, GROUP_TYPE::UI);

	BottomInventoryUi* inventory_ui = DEBUG_NEW BottomInventoryUi();
	inventory_ui->set_group_type(GROUP_TYPE::UI);
	inventory_ui->Init(player);
	CreateGObject(inventory_ui, GROUP_TYPE::UI);
}
