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
bool Scene_Farmhouse::Enter(SCENE_TYPE from)
{
	if (!initialized_) {
		Initialize();
	}
	else {
		Reinitialize();
	}

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
	return true;
}

void Scene_Farmhouse::Initialize()
{
	// �� �ε�
	FileManager::GetInstance()->LoadMap(PathManager::GetInstance()->GetContentPath() + _T("map\\Farmhouse.map"));
	// ī�޶� ����
	Camera::GetInstance()->set_look_pos(Vector2{ 0, 0 });
	
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
		Camera::GetInstance()->set_target(player);
		CreateUis(player);
	}
}

void Scene_Farmhouse::CreateUis(Player* player)
{
	TimerUi* timer_ui = DEBUG_NEW TimerUi();
	timer_ui->set_pos(Vector2(0, 0));
	timer_ui->set_scale(Vector2(200, 100));
	timer_ui->set_group_type(GROUP_TYPE::UI);
	CreateGObject(timer_ui, GROUP_TYPE::UI);

	Texture* texture = ResManager::GetInstance()->LoadTexture(_T("TimerUi_Background"), _T("texture\\light-gray.png"));
	UiSprite* sprite = DEBUG_NEW UiSprite();
	sprite->QuickSet(texture, timer_ui, timer_ui->get_pos(), timer_ui->get_scale());
	timer_ui->ChangeSprite(sprite);

	BottomInventoryUi* inventory_ui = DEBUG_NEW BottomInventoryUi();
	Vector2 resolution = Core::GetInstance()->get_resolution();
	inventory_ui->set_scale(Vector2{ resolution.x * 0.7f, 60.f });
	inventory_ui->set_pos(Vector2{ resolution.x * 0.15f, resolution.y - 60.f });
	inventory_ui->set_group_type(GROUP_TYPE::UI);
	inventory_ui->Init(player);
	CreateGObject(inventory_ui, GROUP_TYPE::UI);
}
