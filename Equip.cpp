#include "Equip.h"
#include "ResManager.h"
#include "ItemSprite.h"
#include "RealObject.h"
#include "IItemHolder.h"
#include "ItemAnimator.h"
#include "SceneManager.h"
#include "FieldTileObject.h"
#include "DropItem.h"
#include "ItemDb.h"
#include "Mic.h"
#include "FmodSound.h"
Equip::~Equip()
{
	delete sprite_;
	delete profile_sprite_;
	delete animator_;
}
IItem* Equip::Init(int item_code, tstring name, tstring description, UINT price)
{
	item_code_ = item_code;
	name_ = name;
	price_ = price;
	description_ = description;
	
	return this;
}

bool Equip::Use(RealObject* obj) const
{
	switch (item_code_) {
	case (int)ITEM_CODE::HOE: {	//괭이
		if (obj && obj->get_item_holder()) {

			// 플레이어의 애니메이션 시작.
			obj->OnUseItem(ITEM_CODE::HOE);
			// 본인 애니메이션 시작.
			switch (obj->get_direction())
			{
			case DIRECTION::UP:
				animator_->Play(_T("Use_Hoe_Back"), true);
				break;
			case DIRECTION::DOWN:
				animator_->Play(_T("Use_Hoe_Front"), true);
				break;
			case DIRECTION::LEFT:
				animator_->Play(_T("Use_Hoe_Left"), true);
				break;
			case DIRECTION::RIGHT:
				animator_->Play(_T("Use_Hoe_Right"), true);
				break;
			}

			Vector2 target_pos = obj->get_item_holder()->get_target_pos();
			Vector2 to_base_pos;
			TileObject* tile_obj = nullptr;
			SceneManager::GetInstance()->get_current_scene()->GetTileObject(target_pos, to_base_pos, tile_obj);
			if (!tile_obj) {
				FieldTileObject* field_tile_obj = new FieldTileObject();
				field_tile_obj->set_pos(to_base_pos);
				field_tile_obj->set_scale(Vector2{ TILE_WIDTH, TILE_HEIGHT });
				field_tile_obj->set_group_type(GROUP_TYPE::TILE_OBJECT);
				field_tile_obj->Init(TILE_OBJECT_TYPE::FIELD);
				CreateGObject(field_tile_obj, GROUP_TYPE::TILE_OBJECT);

				Sound* sound = ResManager::GetInstance()->LoadSound(_T("Hoe_Effect"), _T("sound\\Hoe_Effect.wav"));
				FmodSound::GetInstance()->Play(FmodSound::GetInstance()->GetChannel(), sound, false);
				
				return true;
			}
			return false;
		}
		
		

	} break;
	case (int)ITEM_CODE::WATERING_POT: { //물뿌리개

		// 플레이어의 애니메이션 시작.
		obj->OnUseItem(ITEM_CODE::WATERING_POT);
		// 본인 애니메이션 시작.
		switch (obj->get_direction())
		{
		case DIRECTION::UP:
			animator_->Play(_T("Use_WateringPot_Back"), true);
			break;
		case DIRECTION::DOWN:
			animator_->Play(_T("Use_WateringPot_Front"), true);
			break;
		case DIRECTION::LEFT:
			animator_->Play(_T("Use_WateringPot_Left"), true);
			break;
		case DIRECTION::RIGHT:
			animator_->Play(_T("Use_WateringPot_Right"), true);
			break;
		}
		Sound* sound = ResManager::GetInstance()->LoadSound(_T("WateringPot_Effect"), _T("sound\\WateringPot_Effect.wav"));
		FmodSound::GetInstance()->Play(FmodSound::GetInstance()->GetChannel(), sound, false);

		Vector2 target_pos = obj->get_item_holder()->get_target_pos();
		Vector2 to_base_pos;
		TileObject* tile_obj = nullptr;
		SceneManager::GetInstance()->get_current_scene()->GetTileObject(target_pos, to_base_pos, tile_obj);
		if (tile_obj && tile_obj->get_tile_object_type() == TILE_OBJECT_TYPE::FIELD) {
			FieldTileObject* field_tile_obj = dynamic_cast<FieldTileObject*>(tile_obj);
			field_tile_obj->Water();

			
			return true;
		}
		return false;
		

		

	} break;
	case (int)ITEM_CODE::PICKAXE: { //곡괭이

		// 플레이어의 애니메이션 시작.
		obj->OnUseItem(ITEM_CODE::PICKAXE);
		// 본인 애니메이션 시작.
		switch (obj->get_direction())
		{
		case DIRECTION::UP:
			animator_->Play(_T("Use_Pickaxe_Back"), true);
			break;
		case DIRECTION::DOWN:
			animator_->Play(_T("Use_Pickaxe_Front"), true);
			break;
		case DIRECTION::LEFT:
			animator_->Play(_T("Use_Pickaxe_Left"), true);
			break;
		case DIRECTION::RIGHT:
			animator_->Play(_T("Use_Pickaxe_Right"), true);
			break;
		}

		Vector2 target_pos = obj->get_item_holder()->get_target_pos();
		Vector2 to_base_pos;
		TileObject* tile_obj = nullptr;
		SceneManager::GetInstance()->get_current_scene()->GetTileObject(target_pos, to_base_pos, tile_obj);
		if (tile_obj && tile_obj->get_tile_object_type() == TILE_OBJECT_TYPE::FIELD) {
			DeleteGObject(tile_obj, GROUP_TYPE::TILE_OBJECT);
			
			return true;
		}
		else if (tile_obj && tile_obj->get_tile_object_type() == TILE_OBJECT_TYPE::STONE) {
			DeleteGObject(tile_obj, GROUP_TYPE::TILE_OBJECT);

			const IItem* stone = ItemDb::GetInstance()->get_item(static_cast<int>(ITEM_CODE::STONE));
			DropItem* dropped_stone = DEBUG_NEW DropItem();
			dropped_stone->Init(stone, 1);
			dropped_stone->set_pos(to_base_pos);
			dropped_stone->set_scale(Vector2{ TILE_WIDTH, TILE_HEIGHT });
			dropped_stone->set_group_type(GROUP_TYPE::DROP_ITEM);
			CreateGObject(dropped_stone, GROUP_TYPE::DROP_ITEM);
			Sound* sound = ResManager::GetInstance()->LoadSound(_T("Pickaxe_Effect"), _T("sound\\Pickaxe_Effect.wav"));
			FmodSound::GetInstance()->Play(FmodSound::GetInstance()->GetChannel(), sound, false);
		}
		return false;
		

		
	} break;
	case (int)ITEM_CODE::AXE: { //도끼

		// 플레이어의 애니메이션 시작.
		obj->OnUseItem(ITEM_CODE::AXE);
		// 본인 애니메이션 시작.
		switch (obj->get_direction())
		{
		case DIRECTION::UP:
			animator_->Play(_T("Use_Axe_Back"), true);
			break;
		case DIRECTION::DOWN:
			animator_->Play(_T("Use_Axe_Front"), true);
			break;
		case DIRECTION::LEFT:
			animator_->Play(_T("Use_Axe_Left"), true);
			break;
		case DIRECTION::RIGHT:
			animator_->Play(_T("Use_Axe_Right"), true);
			break;
		}

		Vector2 target_pos = obj->get_item_holder()->get_target_pos();
		Vector2 to_base_pos;
		TileObject* tile_obj = nullptr;
		SceneManager::GetInstance()->get_current_scene()->GetTileObject(target_pos, to_base_pos, tile_obj);
		if (tile_obj && tile_obj->get_tile_object_type() == TILE_OBJECT_TYPE::WOOD) {
			DeleteGObject(tile_obj, GROUP_TYPE::TILE_OBJECT);

			const IItem* wood = ItemDb::GetInstance()->get_item(static_cast<int>(ITEM_CODE::WOOD));
			DropItem* dropped_wood = DEBUG_NEW DropItem();
			dropped_wood->Init(wood, 1);
			dropped_wood->set_pos(to_base_pos);
			dropped_wood->set_scale(Vector2{ TILE_WIDTH, TILE_HEIGHT });
			dropped_wood->set_group_type(GROUP_TYPE::DROP_ITEM);
			CreateGObject(dropped_wood, GROUP_TYPE::DROP_ITEM);

			Sound* sound = ResManager::GetInstance()->LoadSound(_T("Axe_Effect"), _T("sound\\Axe_Effect.wav"));
			FmodSound::GetInstance()->Play(FmodSound::GetInstance()->GetChannel(), sound, false);

			
			return true;
		}
		if (tile_obj && tile_obj->get_tile_object_type() == TILE_OBJECT_TYPE::WEED) {
			DeleteGObject(tile_obj, GROUP_TYPE::TILE_OBJECT);

			const IItem* weed = ItemDb::GetInstance()->get_item(static_cast<int>(ITEM_CODE::WEED));
			DropItem* dropped_weed = DEBUG_NEW DropItem();
			dropped_weed->Init(weed, 1);
			dropped_weed->set_pos(to_base_pos);
			dropped_weed->set_scale(Vector2{ TILE_WIDTH, TILE_HEIGHT });
			dropped_weed->set_group_type(GROUP_TYPE::DROP_ITEM);
			CreateGObject(dropped_weed, GROUP_TYPE::DROP_ITEM);

			Sound* sound = ResManager::GetInstance()->LoadSound(_T("Axe_Effect"), _T("sound\\Axe_Effect.wav"));
			FmodSound::GetInstance()->Play(FmodSound::GetInstance()->GetChannel(), sound, false);


			return true;
		}
		return false;
		
		
	} break;
	}
	return false;
}

int Equip::get_item_code() const
{
	return item_code_;
}

void Equip::UpdateOnHolder(IItemHolder* holder) const
{
	if (holder && holder->get_owner()) {
		if (animator_) animator_->Update();

		
	}

}
void Equip::RenderOnHolder(IItemHolder* holder, ID3D11Device* p_d3d_device) const
{
	if (holder && holder->get_owner()) {
		if (animator_) animator_->Render(p_d3d_device);

	}
}

void Equip::OnHold(RealObject* owner) const
{
	// 선택돼있을 때(캐릭터가 잡고 있을 때)
	if (owner) {
		if(animator_) animator_->set_owner(owner->get_item_holder());

	}
}
