#include "Equip.h"
#include "ResManager.h"
#include "ItemSprite.h"
#include "RealObject.h"
#include "IItemHolder.h"
Equip::~Equip()
{
	delete sprite_;
}
IItem* Equip::Init(int item_code, tstring name)
{
	item_code_ = item_code;
	name_ = name;


	
	return this;
}

void Equip::Use(RealObject* obj)
{
	switch (item_code_) {
	case (int)ITEM_CODE::HOE: {	//±ªÀÌ

	} break;
	case (int)ITEM_CODE::WATERING_POT: { //¹°»Ñ¸®°³

	} break;
	case (int)ITEM_CODE::PICKAXE: { //°î±ªÀÌ

	} break;
	case (int)ITEM_CODE::AXE: { //µµ³¢

	} break;
	}
}

int Equip::get_item_code() const
{
	return item_code_;
}


void Equip::OnHold(RealObject* owner) const
{
	// ¼±ÅÃµÅÀÖÀ» ¶§(Ä³¸¯ÅÍ°¡ Àâ°í ÀÖÀ» ¶§)
	owner->get_item_holder()->SetItem(this);
}
