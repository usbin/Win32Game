#include "ItemDb.h"
#include "Equip.h"
#include "Crop.h"
#include "Mic.h"
#include "Seed.h"

void ItemDb::Init()
{
	items_.insert(std::make_pair<int, IItem*>((int)ITEM_CODE::HOE,				(DEBUG_NEW Equip())->Init((int)ITEM_CODE::HOE, _T("����"))));
	items_.insert(std::make_pair<int, IItem*>((int)ITEM_CODE::WATERING_POT,		(DEBUG_NEW Equip())->Init((int)ITEM_CODE::HOE, _T("���Ѹ���"))));
	items_.insert(std::make_pair<int, IItem*>((int)ITEM_CODE::PICKAXE,			(DEBUG_NEW Equip())->Init((int)ITEM_CODE::PICKAXE, _T("���"))));
	items_.insert(std::make_pair<int, IItem*>((int)ITEM_CODE::AXE,				(DEBUG_NEW Equip())->Init((int)ITEM_CODE::AXE, _T("����"))));
	items_.insert(std::make_pair<int, IItem*>((int)ITEM_CODE::SICKLE,			(DEBUG_NEW Equip())->Init((int)ITEM_CODE::SICKLE, _T("��"))));

	items_.insert(std::make_pair<int, IItem*>((int)ITEM_CODE::STONE,			(DEBUG_NEW Mic())->Init((int)ITEM_CODE::STONE, _T("��"))));
	items_.insert(std::make_pair<int, IItem*>((int)ITEM_CODE::WEED,				(DEBUG_NEW Mic())->Init((int)ITEM_CODE::WEED, _T("����"))));
	items_.insert(std::make_pair<int, IItem*>((int)ITEM_CODE::WOOD,				(DEBUG_NEW Mic())->Init((int)ITEM_CODE::WOOD, _T("����"))));

	items_.insert(std::make_pair<int, IItem*>((int)ITEM_CODE::PARSNIP_SEED,		(DEBUG_NEW Seed())->Init((int)ITEM_CODE::PARSNIP_SEED, _T("���� ����"))));
	items_.insert(std::make_pair<int, IItem*>((int)ITEM_CODE::PARSNIP,			(DEBUG_NEW Crop())->Init((int)ITEM_CODE::PARSNIP, _T("����"))));

}

const IItem* ItemDb::GetItem(int item_code)
{
	auto it = items_.find(item_code);
	if (it != items_.end()) {
		return it->second;
	}
	return nullptr;
}
