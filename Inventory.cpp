#include "Inventory.h"
#include "Player.h"
#include "IItem.h"
#include "ItemData.h"
#include "ItemDb.h"
#include "IUsable.h"
#include "Equip.h"
Inventory::~Inventory()
{
	SafeDeleteVector<ItemData*>(items_);
}

void Inventory::Init(Player* player)
{
	owner_ = player;
	for (int i = 0; i < MAX_INVENTORY_SIZE; i++) {
		items_.push_back(nullptr);
	}


	const IItem* item = ItemDb::GetInstance()->get_item((int)ITEM_CODE::HOE);
	const IItem* item2 = ItemDb::GetInstance()->get_item((int)ITEM_CODE::WATERING_POT);
	const IItem* item3 = ItemDb::GetInstance()->get_item((int)ITEM_CODE::PICKAXE);
	const IItem* item4 = ItemDb::GetInstance()->get_item((int)ITEM_CODE::AXE);
	const IItem* item5 = ItemDb::GetInstance()->get_item((int)ITEM_CODE::STONE);
	const IItem* item6 = ItemDb::GetInstance()->get_item((int)ITEM_CODE::PARSNIP_SEED);
	const IItem* item7 = ItemDb::GetInstance()->get_item((int)ITEM_CODE::PARSNIP);

	AddItem(item, 1);
	AddItem(item2, 1);
	AddItem(item3, 1);
	AddItem(item4, 1);
	AddItem(item5, 1);
	AddItem(item6, 1);
	AddItem(item7, 1);
	
}

void Inventory::AddHandler(OnInventoryDataChanged handler, OnInventoryDataChangedArgs args)
{
	handlers_.push_back(OnInventoryDataChangedData{ handler, args });
}

const ItemData* Inventory::GetItem(int index)
{
	if (items_.size() > index && items_[index]) return items_[index];
	else nullptr;
}

bool Inventory::UseItem(int index, int amount)
{
	if (items_.size() > index && items_[index]) {
		//갖고 있는 아이템의 수가 사용하려는 수보다 작으면 안 됨.
		if (items_[index]->amount >= amount) {

			const IItem* item = items_[index]->item;
			if (item) {
				//아이템 사용 처리
				//1. 사용 가능한 아이템일 경우 사용 함수 실행.
				const IUsable* usable_item = dynamic_cast<const IUsable*>(item);
				if (usable_item) {
					if (usable_item->Use(owner_)) {
						//2. 장비 아이템이면 사용해도 개수 줄어들지 않음.
						//	그 외의 경우 사용하면 개수 줄어듦.
						if (!dynamic_cast<const Equip*>(items_[index]->item)) {
							items_[index]->amount = items_[index]->amount - amount;
						}
						//	사용 후에 아이템이 0개가 됐을 경우. 인벤토리에서 삭제 처리.
						if (items_[index]->amount <= 0) {
							delete items_[index];
							items_[index] = nullptr;
						}
						//3. 인벤토리 변경 이벤트 핸들러 실행
						for (int i = 0; i < handlers_.size(); i++) {
							handlers_[i].handler(this, index, items_[index], handlers_[i].args);
						}
						return true;
					}
				}
			}
		}


		
	}
	return false;
}

bool Inventory::AddItem(const IItem* item, int amount)
{
	//넣을 자리 찾기
	//1순위: 스택이 가득 차지 않은 같은 아이템
	int result_i = items_.size();
	for (int i = 0; i < items_.size(); i++) {
		if (items_[i] && items_[i]->item == item && items_[i]->item->get_max_stack() >= amount + items_[i]->amount) {
			result_i = i;
			break;
		}
	}
	//2순위: 빈 자리
	if (result_i >= items_.size()) {
		for (int i = 0; i < items_.size(); i++) {
			if (!items_[i]) {
				result_i = i;
				break;
			}
		}
	}

	//자리를 찾지 못했을 경우.
	if (result_i >= items_.size()) return false;
	


	//찾은 자리가 빈 칸일 경우
	if (!items_[result_i]) {
		items_[result_i] = DEBUG_NEW ItemData{ item, amount };

	}
	//3.찾은 자리에 이미 아이템이 존재할 경우
	else {
		items_[result_i]->amount += amount;
	}

	//인벤토리 변경 이벤트 핸들러 실행
	for (int j = 0; j < handlers_.size(); j++) {
		handlers_[j].handler(this, result_i, items_[result_i], handlers_[j].args);
	}
	return true;
}

const std::vector<ItemData*>& Inventory::GetItems()
{
	return items_;
}
