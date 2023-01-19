#include "PlayerItemHolder.h"
#include "IItem.h"
#include "Player.h"
#include "ItemSprite.h"
#include "TileObject.h"
#include "SceneManager.h"
#include "Inventory.h"
#include "ItemData.h"
PlayerItemHolder::PlayerItemHolder()
{
	holder_scale_ = Vector2{ 48, 48 };
	hold_offset_ = Vector2{ 0, 0 };
}

PlayerItemHolder::~PlayerItemHolder()
{
}


void PlayerItemHolder::Update()
{
	if (owner_ && !owner_->IsDead() && owner_->get_inventory()) {
		// 아이템 정보 업데이트
		
		SetItem(index_);

		// 아이템 업데이트
		const ItemData* item_data = GetItemData();
		if(item_data) item_data->item->UpdateOnHolder(this);

		switch (owner_->get_direction())
		{
		case DIRECTION::UP:
		{
			target_pos_ = owner_->get_pos() + Vector2{ 0.f, -.5f * (float)TILE_HEIGHT};
		}	break;
		case DIRECTION::DOWN:
			target_pos_ = owner_->get_pos() + Vector2{ 0.f, 1.5f * (float)TILE_HEIGHT};
			break;
		case DIRECTION::LEFT:
			target_pos_ = owner_->get_pos() + Vector2{ -1.f * (float)TILE_WIDTH, .5f*(float)TILE_HEIGHT};
			break;
		case DIRECTION::RIGHT:
			target_pos_ = owner_->get_pos() + Vector2{ 1.f * (float)TILE_WIDTH, .5f*(float)TILE_HEIGHT};
			break;
		}
	}
}

void PlayerItemHolder::Render(ID3D11Device* p_d3d_device)
{
	const ItemData* item_data = GetItemData();
	if (item_data) {
		item_data->item->RenderOnHolder(this, p_d3d_device);
		Vector2 tile_obj_base_pos{ 0, 0 };
		TileObject* p_tile_obj = nullptr;
		SceneManager::GetInstance()->get_current_scene()->GetTileObject(
			target_pos_
			, tile_obj_base_pos
			, p_tile_obj);
		DrawRectangle(p_d3d_device, WorldToRenderPos(tile_obj_base_pos - Vector2{ TILE_WIDTH, TILE_HEIGHT }/2.f), Vector2{ TILE_WIDTH, TILE_HEIGHT }, ARGB(0xFFFF0000), 1);
	}
	
}


void PlayerItemHolder::SetItem(int index)
{

	if (owner_ && owner_->get_inventory()) {
		index_ = index;
		if (index_ >= 0) {
			const ItemData* item_data = GetItemData();
			if (item_data && item_data->item) {
				owner_->OnHold(item_data->item);
				item_data->item->OnHold(owner_);
			}
			else owner_->OnUnhold();
		}
		else owner_->OnUnhold();
	}
}

bool PlayerItemHolder::UseItem()
{
	if (owner_) {
		return owner_->get_inventory()->UseItem(index_, 1);
	}
	return false;
}

const ItemData* PlayerItemHolder::GetItemData()
{
	if (owner_ && owner_->get_inventory()) {
		return owner_->get_inventory()->GetItem(index_);
	}
	return nullptr;
}

Vector2 PlayerItemHolder::get_target_pos()
{
	return target_pos_;
}
