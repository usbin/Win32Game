#include "FieldTileObject.h"
#include "Seed.h"
#include "TileObjectRenderComponent.h"
#include "SceneManager.h"
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

}

void FieldTileObject::SetSeed(const Seed* seed, UINT level)
{
	seed_ = seed;
	level_ = level;

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

void FieldTileObject::Update()
{
}

void FieldTileObject::Render(ID3D11Device* p_d3d_device)
{
	render_cmp_->Render(this, p_d3d_device);
	//crop 렌더
	if (seed_) {
		ItemSprite* item_sprite = seed_->get_level_sprite(level_);
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
