#include "Equip.h"


IItem* Equip::Init(int item_code, tstring name)
{
	item_code_ = item_code;
	name_ = name;

	//
	//(0, 24) (15, 48)
	switch (item_code) {
	case (int)ITEM_CODE::HOE: {	//����

	} break;
	case (int)ITEM_CODE::WATERING_POT: { //���Ѹ���

	} break;
	case (int)ITEM_CODE::PICKAXE: { //���

	} break;
	case (int)ITEM_CODE::AXE: { //����

	} break;
	case (int)ITEM_CODE::SICKLE: { //��

	} break;
	}
	return this;
}

void Equip::Use(GObject* obj)
{
	switch (item_code_) {
	case (int)ITEM_CODE::HOE: {	//����

	} break;
	case (int)ITEM_CODE::WATERING_POT: { //���Ѹ���

	} break;
	case (int)ITEM_CODE::PICKAXE: { //���

	} break;
	case (int)ITEM_CODE::AXE: { //����

	} break;
	case (int)ITEM_CODE::SICKLE: { //��

	} break;
	}
}

int Equip::get_item_code()
{
	return item_code_;
}

void Equip::OnHold(GObject* owner)
{
	// ���õ����� ��(ĳ���Ͱ� ��� ���� ��)

}
