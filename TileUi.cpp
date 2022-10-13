#include "TileUi.h"
#include "SceneManager.h"
#include "TileEditUi.h"
#include "Sprite.h"
#include "Director_Scene_Tool.h"

TileUi::TileUi(bool is_static_pos)
	: Ui(is_static_pos)
	, is_dragging_(false)
{
}

TileUi::~TileUi()
{
}

void TileUi::Update()
{
	Ui::Update();
	
	
	if (KEY_UP(KEY::LBUTTON)) {
		if (is_dragging_) {
			is_dragging_ = false;
			director_->InsertTile(GET_MOUSE_POS(), this);
		}
	}
	else if (KEY_DOWN(KEY::LBUTTON)) {
		if (is_picked_) {
			director_->InsertTile(GET_MOUSE_POS(), this);
		}
	}


	ChildrenUpdate();
}

void TileUi::Render(HDC hdc)
{
	Ui::Render(hdc);
	
	switch (director_->get_mode()) {
	case TILE_EDIT_MODE::ADD: {
		if (is_dragging_ || is_picked_) {
			Sprite* sprite = get_sprite();
			Vector2 mouse_pos = WorldToRenderPos( GET_MOUSE_POS() );
			TransparentBlt(hdc
				, mouse_pos.x - get_scale().x/2.f, mouse_pos.y - get_scale().y/2.f, get_scale().x, get_scale().y
				, sprite->get_texture()->get_hdc(), sprite->get_base_pos().x, sprite->get_base_pos().y, sprite->get_scale().x, sprite->get_scale().y, RGB(255, 0, 255));
		}
	}
	break;
	
	}

	ChildrenRender(hdc);
}

void TileUi::LbuttonClick()
{
}

void TileUi::LbuttonDown()
{
	switch (director_->get_mode()) {
	case TILE_EDIT_MODE::ADD: {
		prev_drag_pos_ = GET_MOUSE_POS();
		drag_preview_pos_ = get_final_pos();
		is_dragging_ = true;
	}
	break;
	}
	
}

void TileUi::LbuttonUp()
{

}


void TileUi::IncreasePriority()
{
	//Tile 목록에서 뒤로 보내기
	SceneManager::GetInstance()->get_current_scene()->ObjectToNext(GROUP_TYPE::UI, this);
}

void TileUi::DecreasePriority()
{
	//Tile 목록에서 앞으로 보내기
	SceneManager::GetInstance()->get_current_scene()->ObjectToPrev(GROUP_TYPE::UI, this);
}
