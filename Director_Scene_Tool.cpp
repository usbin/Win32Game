#include "Director_Scene_Tool.h"
#include "TileEditUi.h"
#include "ButtonUi.h"
#include "TileCell.h"
#include "TileUi.h"
#include "Sprite.h"

#define TILE_WINDOW_WIDTH 300
#define TILE_WINDOW_HEIGHT 550
Director_Scene_Tool::Director_Scene_Tool()
	: tile_edit_ui_(nullptr)
	, mode_(TILE_EDIT_MODE::ADD)
{
}

Director_Scene_Tool::~Director_Scene_Tool()
{
}

void Director_Scene_Tool::Update()
{
	if (KEY_DOWN(KEY::T)) {
		//T 눌리면 타일 UI 열기/닫기
		if (tile_edit_ui_ == nullptr
			|| tile_edit_ui_->IsDead()) {
			TileEditUi* tdu = new TileEditUi();
			tdu->set_pos(Vector2{ 500, 100 });
			tdu->set_scale(Vector2{ TILE_WINDOW_WIDTH, TILE_WINDOW_HEIGHT });
			tdu->set_group_type(GROUP_TYPE::UI);
			tdu->set_name(_T("Tile Edit Ui"));
			tdu->set_director(this);
			tdu->Init();
			CreateGObject(tdu, GROUP_TYPE::UI);
			tile_edit_ui_ = tdu;
			ChangeMode(TILE_EDIT_MODE::ADD);
		}
		else{
			DeleteGObject(tile_edit_ui_, GROUP_TYPE::UI);
			tile_edit_ui_ = nullptr;
			
		}
	}
	if (KEY_DOWN(KEY::TAB)) {
		ChangeScene(SCENE_TYPE::TITLE);
	}
}

void Director_Scene_Tool::ChangeMode(TILE_EDIT_MODE mode)
{
	ButtonUi** mode_buttons = tile_edit_ui_->get_mode_buttons();
	mode_buttons[static_cast<ULONGLONG>(mode_)]->set_selected(false);
	mode_buttons[static_cast<ULONGLONG>(mode)]->set_selected(true);
	mode_ = mode;


}

void Director_Scene_Tool::CreateEmptyTilemap(const Vector2& tile_size, const Vector2& tile_count)
{
	for (int i = 0; i < tile_count.y; i++) {
		for (int j = 0; j < tile_count.x; j++) {
			TileCell* tile_cell = new TileCell();
			tile_cell->set_pos(Vector2{ (static_cast<int>(j * tile_size.x)) % static_cast<int>(tile_count.x*tile_size.x), static_cast<int>((i * tile_size.y)) });
			tile_cell->set_scale(tile_size);
			tile_cell->set_group_type(GROUP_TYPE::TILE);
			tile_cell->set_name(_T("Tile Cell"));
			CreateGObject(tile_cell, GROUP_TYPE::TILE);
			tile_map_.push_back(tile_cell);
		}
	}
}

void Director_Scene_Tool::InsertTile(const Vector2& mouse_pos, TileUi* tile_ui)
{
	//moues_pos가 타일맵 안에 있을 경우에만

	//몇번째 타일맵인지 찾고 삽입
	for (int i = 0; i < tile_map_.size(); i++) {
		Vector2 tile_pos = tile_map_[i]->get_pos();
		Vector2 tile_scale = tile_map_[i]->get_scale();
		if (tile_pos.x < mouse_pos.x && mouse_pos.x < tile_pos.x + tile_scale.x
			&& tile_pos.y < mouse_pos.y && mouse_pos.y < tile_pos.y + tile_scale.y) {
			
			tile_map_[i]->SetTileCell(tile_ui);
		}
	}
}