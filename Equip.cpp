#include "Equip.h"
#include "ResManager.h"
#include "ItemSprite.h"
#include "RealObject.h"
#include "IItemHolder.h"
#include "ItemAnimator.h"
#include "SceneManager.h"
#include "FieldTileObject.h"
Equip::~Equip()
{
	delete sprite_;
	delete animator_;
}
IItem* Equip::Init(int item_code, tstring name)
{
	item_code_ = item_code;
	name_ = name;


	
	return this;
}

bool Equip::Use(RealObject* obj) const
{
	switch (item_code_) {
	case (int)ITEM_CODE::HOE: {	//����
		if (obj && obj->get_item_holder()) {
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

				// �÷��̾��� �ִϸ��̼� ����.
				obj->OnUseItem(ITEM_CODE::HOE);
				// ���� �ִϸ��̼� ����.
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
				return true;
			}
			return false;
		}
		
		

	} break;
	case (int)ITEM_CODE::WATERING_POT: { //���Ѹ���
		Vector2 target_pos = obj->get_item_holder()->get_target_pos();
		Vector2 to_base_pos;
		TileObject* tile_obj = nullptr;
		SceneManager::GetInstance()->get_current_scene()->GetTileObject(target_pos, to_base_pos, tile_obj);
		if (tile_obj && tile_obj->get_tile_object_type() == TILE_OBJECT_TYPE::FIELD) {
			FieldTileObject* field_tile_obj = dynamic_cast<FieldTileObject*>(tile_obj);
			field_tile_obj->Water();
			// �÷��̾��� �ִϸ��̼� ����.
			obj->OnUseItem(ITEM_CODE::WATERING_POT);
			// ���� �ִϸ��̼� ����.
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
			return true;
		}
		return false;
		

		

	} break;
	case (int)ITEM_CODE::PICKAXE: { //���

		Vector2 target_pos = obj->get_item_holder()->get_target_pos();
		Vector2 to_base_pos;
		TileObject* tile_obj = nullptr;
		SceneManager::GetInstance()->get_current_scene()->GetTileObject(target_pos, to_base_pos, tile_obj);
		if (tile_obj && tile_obj->get_tile_object_type() == TILE_OBJECT_TYPE::FIELD) {
			delete tile_obj;

			// �÷��̾��� �ִϸ��̼� ����.
			obj->OnUseItem(ITEM_CODE::PICKAXE);
			// ���� �ִϸ��̼� ����.
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
			return true;
		}
		return false;
		

		
	} break;
	case (int)ITEM_CODE::AXE: { //����
		Vector2 target_pos = obj->get_item_holder()->get_target_pos();
		Vector2 to_base_pos;
		TileObject* tile_obj = nullptr;
		SceneManager::GetInstance()->get_current_scene()->GetTileObject(target_pos, to_base_pos, tile_obj);
		if (tile_obj && tile_obj->get_tile_object_type() == TILE_OBJECT_TYPE::WOOD) {
			delete tile_obj;
			// �÷��̾��� �ִϸ��̼� ����.
			obj->OnUseItem(ITEM_CODE::AXE);
			// ���� �ִϸ��̼� ����.
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
	// ���õ����� ��(ĳ���Ͱ� ��� ���� ��)
	if (owner) {
		if(animator_) animator_->set_owner(owner->get_item_holder());

	}
}
