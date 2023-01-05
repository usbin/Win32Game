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
	case (int)ITEM_CODE::HOE: {	//����
		// �÷��̾��� �ִϸ��̼� ����.
		obj->OnUseItem(ITEM_CODE::HOE);
		// ���� �ִϸ��̼� ����.
		animator_->Play(_T("Use_Hoe_Front"), true);
		
	} break;
	case (int)ITEM_CODE::WATERING_POT: { //���Ѹ���

	} break;
	case (int)ITEM_CODE::PICKAXE: { //���

	} break;
	case (int)ITEM_CODE::AXE: { //����

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
void Equip::OnUnhold() const
{
	if(animator_) animator_->set_owner(nullptr);
}


void Equip::OnHold(RealObject* owner) const
{
	// ���õ����� ��(ĳ���Ͱ� ��� ���� ��)
	if (owner) {
		owner->get_item_holder()->SetItem(this);
		if(animator_) animator_->set_owner(owner->get_item_holder());

	}
}
