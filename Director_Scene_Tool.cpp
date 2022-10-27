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
			tile_edit_ui_->ChangeMode(TILE_EDIT_MODE::ADD);
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
