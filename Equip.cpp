#include "Equip.h"
#include "ResManager.h"
#include "ItemSprite.h"
#include "RealObject.h"
#include "IItemHolder.h"
#include "ItemAnimator.h"
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

void Equip::Use(RealObject* obj) const
{
	switch (item_code_) {
	case (int)ITEM_CODE::HOE: {	//괭이
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
	} break;
	}
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
