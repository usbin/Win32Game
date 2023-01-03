#include "ItemDb.h"
#include "Equip.h"
#include "Crop.h"
#include "Mic.h"
#include "Seed.h"

void ItemDb::Init()
{
	items_.insert(std::make_pair<int, IItem*>((int)ITEM_CODE::HOE,				(DEBUG_NEW Equip())->Init((int)ITEM_CODE::HOE, _T("±ªÀÌ"))));
	items_.insert(std::make_pair<int, IItem*>((int)ITEM_CODE::WATERING_POT,		(DEBUG_NEW Equip())->Init((int)ITEM_CODE::HOE, _T("¹°»Ñ¸®°³"))));
	items_.insert(std::make_pair<int, IItem*>((int)ITEM_CODE::PICKAXE,			(DEBUG_NEW Equip())->Init((int)ITEM_CODE::PICKAXE, _T("°î±ªÀÌ"))));
	items_.insert(std::make_pair<int, IItem*>((int)ITEM_CODE::AXE,				(DEBUG_NEW Equip())->Init((int)ITEM_CODE::AXE, _T("µµ³¢"))));
	items_.insert(std::make_pair<int, IItem*>((int)ITEM_CODE::SICKLE,			(DEBUG_NEW Equip())->Init((int)ITEM_CODE::SICKLE, _T("³´"))));

	items_.insert(std::make_pair<int, IItem*>((int)ITEM_CODE::STONE,			(DEBUG_NEW Mic())->Init((int)ITEM_CODE::STONE, _T("µ¹"))));
	items_.insert(std::make_pair<int, IItem*>((int)ITEM_CODE::WEED,				(DEBUG_NEW Mic())->Init((int)ITEM_CODE::WEED, _T("ÀâÃÊ"))));
	items_.insert(std::make_pair<int, IItem*>((int)ITEM_CODE::WOOD,				(DEBUG_NEW Mic())->Init((int)ITEM_CODE::WOOD, _T("³ª¹«"))));

	items_.insert(std::make_pair<int, IItem*>((int)ITEM_CODE::PARSNIP_SEED,		(DEBUG_NEW Seed())->Init((int)ITEM_CODE::PARSNIP_SEED, _T("¼ø¹« ¾¾¾Ñ"))));
	items_.insert(std::make_pair<int, IItem*>((int)ITEM_CODE::PARSNIP,			(DEBUG_NEW Crop())->Init((int)ITEM_CODE::PARSNIP, _T("¼ø¹«"))));

}

const IItem* ItemDb::GetItem(int item_code)
{
	auto it = items_.find(item_code);
	if (it != items_.end()) {
		return it->second;
	}
	return nullptr;
}
