#include "FieldTileObject.h"
#include "Seed.h"
#include "TileObjectRenderComponent.h"
#include "SceneManager.h"
#include "DropItem.h"
#include "ItemDb.h"
#include "Interactor.h"
#include "Player.h"
#include "PlayerItemHolder.h"
FieldTileObject::FieldTileObject()
{
}

FieldTileObject::~FieldTileObject()
{
	//4방향 연결 체크
	//4방향 연결 여부 체크
	Vector2 tile_base_pos{};
	TileObject* target_tile_obj_up = nullptr;
	TileObject* target_tile_obj_right = nullptr;
	TileObject* target_tile_obj_down = nullptr;
	TileObject* target_tile_obj_left = nullptr;

	Vector2 up_pos = get_pos() + Vector2{ 0, -TILE_HEIGHT };
	Vector2 right_pos = get_pos() + Vector2{ TILE_WIDTH, 0 };
	Vector2 down_pos = get_pos() + Vector2{ 0, TILE_HEIGHT };
	Vector2 left_pos = get_pos() + Vector2{ -TILE_WIDTH, 0 };
	SceneManager::GetInstance()->get_current_scene()->GetTileObject(up_pos, tile_base_pos, target_tile_obj_up);
	SceneManager::GetInstance()->get_current_scene()->GetTileObject(right_pos, tile_base_pos, target_tile_obj_right);
	SceneManager::GetInstance()->get_current_scene()->GetTileObject(down_pos, tile_base_pos, target_tile_obj_down);
	SceneManager::GetInstance()->get_current_scene()->GetTileObject(left_pos, tile_base_pos, target_tile_obj_left);
	if (target_tile_obj_up) {
		FieldTileObject* field_up = dynamic_cast<FieldTileObject*>(target_tile_obj_up);
		field_up->SetDisconnected(FIELD_CONNECTED_DOWN);
	}
	if (target_tile_obj_right) {
		FieldTileObject* field_right = dynamic_cast<FieldTileObject*>(target_tile_obj_right);
		field_right->SetDisconnected(FIELD_CONNECTED_LEFT);
	}
	if (target_tile_obj_down) {
		FieldTileObject* field_down = dynamic_cast<FieldTileObject*>(target_tile_obj_down);
		field_down->SetDisconnected(FIELD_CONNECTED_UP);
	}
	if (target_tile_obj_left) {
		FieldTileObject* field_left = dynamic_cast<FieldTileObject*>(target_tile_obj_left);
		field_left->SetDisconnected(FIELD_CONNECTED_RIGHT);
	}
}

void FieldTileObject::Init(TILE_OBJECT_TYPE tile_object_type_)
{
	TileObject::Init(tile_object_type_);
	//4방향 연결 여부 체크
	Vector2 tile_base_pos{};
	TileObject* target_tile_obj_up = nullptr;
	TileObject* target_tile_obj_right = nullptr;
	TileObject* target_tile_obj_down = nullptr;
	TileObject* target_tile_obj_left = nullptr;

	Vector2 up_pos = get_pos() + Vector2{ 0, -TILE_HEIGHT };
	Vector2 right_pos = get_pos() + Vector2{ TILE_WIDTH, 0 };
	Vector2 down_pos = get_pos() + Vector2{ 0, TILE_HEIGHT };
	Vector2 left_pos = get_pos() + Vector2{ -TILE_WIDTH, 0 };
	SceneManager::GetInstance()->get_current_scene()->GetTileObject(up_pos, tile_base_pos, target_tile_obj_up);
	SceneManager::GetInstance()->get_current_scene()->GetTileObject(right_pos, tile_base_pos, target_tile_obj_right);
	SceneManager::GetInstance()->get_current_scene()->GetTileObject(down_pos, tile_base_pos, target_tile_obj_down);
	SceneManager::GetInstance()->get_current_scene()->GetTileObject(left_pos, tile_base_pos, target_tile_obj_left);
	field_connected_ = 0;
	water_connected_ = 0;
	if (target_tile_obj_up) {
		field_connected_ |= FIELD_CONNECTED_UP;
		FieldTileObject* field_up = dynamic_cast<FieldTileObject*>(target_tile_obj_up);
		field_up->SetConnected(FIELD_CONNECTED_DOWN);
	}
	if (target_tile_obj_right) {
		field_connected_ |= FIELD_CONNECTED_RIGHT;
		FieldTileObject* field_right = dynamic_cast<FieldTileObject*>(target_tile_obj_right);
		field_right->SetConnected(FIELD_CONNECTED_LEFT);
	}
	if (target_tile_obj_down) {
		field_connected_ |= FIELD_CONNECTED_DOWN;
		FieldTileObject* field_down = dynamic_cast<FieldTileObject*>(target_tile_obj_down);
		field_down->SetConnected(FIELD_CONNECTED_UP);
	}
	if (target_tile_obj_left) {
		field_connected_ |= FIELD_CONNECTED_LEFT;
		FieldTileObject* field_left = dynamic_cast<FieldTileObject*>(target_tile_obj_left);
		field_left->SetConnected(FIELD_CONNECTED_RIGHT);
	}
	CreateInteractor();
}

void FieldTileObject::CreateInteractor()
{

	Interactor* interactor = DEBUG_NEW Interactor();
	interactor->Init(this, Vector2{ 0, 0 }, get_scale());
	CreateGObject(interactor, GROUP_TYPE::INTERACTOR);
	set_interactor(interactor);
}

void FieldTileObject::SetSeed(const Seed* seed)
{
	seed_ = seed;
	seed_day_ = Game::GetInstance()->get_day();

}

void FieldTileObject::Water()
{
	watered_ = true;

	//4방향 연결 여부 체크
	Vector2 tile_base_pos{};
	TileObject* target_tile_obj_up = nullptr;
	TileObject* target_tile_obj_right = nullptr;
	TileObject* target_tile_obj_down = nullptr;
	TileObject* target_tile_obj_left = nullptr;

	Vector2 up_pos = get_pos() + Vector2{ 0, -TILE_HEIGHT };
	Vector2 right_pos = get_pos() + Vector2{ TILE_WIDTH, 0 };
	Vector2 down_pos = get_pos() + Vector2{ 0, TILE_HEIGHT };
	Vector2 left_pos = get_pos() + Vector2{ -TILE_WIDTH, 0 };
	SceneManager::GetInstance()->get_current_scene()->GetTileObject(up_pos, tile_base_pos, target_tile_obj_up);
	SceneManager::GetInstance()->get_current_scene()->GetTileObject(right_pos, tile_base_pos, target_tile_obj_right);
	SceneManager::GetInstance()->get_current_scene()->GetTileObject(down_pos, tile_base_pos, target_tile_obj_down);
	SceneManager::GetInstance()->get_current_scene()->GetTileObject(left_pos, tile_base_pos, target_tile_obj_left);
	if (target_tile_obj_up) {
		FieldTileObject* field_up = dynamic_cast<FieldTileObject*>(target_tile_obj_up);
		if (field_up->is_watered()) {
			water_connected_ |= FIELD_CONNECTED_UP;
			field_up->SetWaterConnected(FIELD_CONNECTED_DOWN);
		}
	}
	if (target_tile_obj_right) {
		FieldTileObject* field_right = dynamic_cast<FieldTileObject*>(target_tile_obj_right);
		if (field_right->is_watered()) {
			water_connected_ |= FIELD_CONNECTED_RIGHT;
			field_right->SetWaterConnected(FIELD_CONNECTED_LEFT);
		}
	}
	if (target_tile_obj_down) {
		FieldTileObject* field_down = dynamic_cast<FieldTileObject*>(target_tile_obj_down);
		if (field_down->is_watered()) {
			water_connected_ |= FIELD_CONNECTED_DOWN;
			field_down->SetWaterConnected(FIELD_CONNECTED_UP);
		}
	}
	if (target_tile_obj_left) {
		FieldTileObject* field_left = dynamic_cast<FieldTileObject*>(target_tile_obj_left);
		if (field_left->is_watered()) {
			water_connected_ |= FIELD_CONNECTED_LEFT;
			field_left->SetWaterConnected(FIELD_CONNECTED_RIGHT);
		}
	}
}

void FieldTileObject::Harvest()
{
	//해당 위치의 작물을 DropItem으로 뱉어내고...
	//본인을 빈 땅으로 초기화
	DropItem* drop = DEBUG_NEW DropItem();
	drop->Init(ItemDb::GetInstance()->get_item(seed_->get_item_code()), 1);
	drop->set_pos(get_pos());
	drop->set_scale(get_scale());
	drop->set_name(_T("수확된 순무"));
	drop->set_group_type(GROUP_TYPE::DROP_ITEM);
	CreateGObject(drop, GROUP_TYPE::DROP_ITEM);

	SetSeed(nullptr);
	SetLevel(0);
}

void FieldTileObject::Update()
{
	//날짜가 바뀌었을 때의 동작
	UINT today = Game::GetInstance()->get_day();
	if (get_updated_day() < today) {
		if (watered_) {
			//현재 날짜를 seed_day_와 비교해 현재 작물 성장 상태를 동기화
			if (seed_day_ + get_level() < today && get_level() < seed_->get_max_level()) {
				if (today < seed_day_) return;	//오늘보다 이후에 심어졌을 수는 없음.
				SetLevel(today - seed_day_);
			}
			watered_ = false;
			water_connected_ = 0;
		}
		UpdateDay(today);
		
	}
	
}

void FieldTileObject::Render(ID3D11Device* p_d3d_device)
{
	render_cmp_->Render(this, p_d3d_device);
	//crop 렌더
	if (seed_) {
		ItemSprite* item_sprite = seed_->get_level_sprite(get_level());
		seed_->RenderOnField(this, p_d3d_device);
	}


	ComponentRender(p_d3d_device);
}

void FieldTileObject::SetConnected(int connected_field)
{
	field_connected_ |= connected_field;
}

void FieldTileObject::SetDisconnected(int connected_field)
{
	field_connected_ &= ~connected_field;
	water_connected_ &= ~connected_field;
}

void FieldTileObject::SetWaterConnected(int connected_water)
{
	water_connected_ |= connected_water;
}

void FieldTileObject::OnInteract(const GObject* req_obj)
{
	//플레이어이고, 맨손이라면 수확
	if (req_obj->get_group_type() == GROUP_TYPE::PLAYER && seed_ && get_level() >= seed_->get_max_level()) {
		const Player* player = dynamic_cast<const Player*>(req_obj);
		if (!player->get_item_holder() || !player->get_item_holder()->GetItemData()) {
			Harvest();
		}
	}
	
}
