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
	//handler 삭제
	item_handlers_.clear();
	gold_handlers_.clear();

	owner_ = player;
	for (int i = 0; i < CELL_COUNT_MAX; i++) {
		items_.push_back(nullptr);
	}

	
	
}

void Inventory::AddTmpData()
{
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
	AddItem(item6, 5);
	AddItem(item7, 1);
}

void Inventory::AddItemHandler(OnInventoryItemChanged handler, OnInventoryItemChangedArgs args)
{
	item_handlers_.push_back(OnInventoryItemChangedData{ handler, args });
}

void Inventory::RemoveItemHandler(GObject* sender)
{
	for (int i = item_handlers_.size()-1; i >=0; i--) {
		if (item_handlers_[i].args.sender == reinterpret_cast<DWORD_PTR>(sender)) {
			item_handlers_.erase(item_handlers_.begin() + i);
		}
	}
}

void Inventory::AddGoldHander(OnInventoryGoldChanged handler, OnInventoryGoldChangedArgs args)
{
	gold_handlers_.push_back(OnInventoryGoldChangedData{ handler, args });
}

void Inventory::RemoveGoldHandler(GObject* sender)
{
	for (int i = gold_handlers_.size() - 1; i >= 0; i--) {
		if (gold_handlers_[i].args.sender == reinterpret_cast<DWORD_PTR>(sender)) {
			gold_handlers_.erase(gold_handlers_.begin() + i);
		}
	}
}

const ItemData* Inventory::GetItem(int index)
{
	if (index>= 0 &&items_.size() > index && items_[index]) 
		return items_[index];
	else 
		return nullptr;
}

bool Inventory::UseItem(int index, int amount)
{
	if (index>=0 && items_.size() > index && items_[index]) {
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
						for (int i = 0; i < item_handlers_.size(); i++) {
							item_handlers_[i].handler(this, index, items_[index], item_handlers_[i].args);
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
	int remain_amount = amount;
	for (int i = 0; i < items_.size(); i++) {
		if (items_[i] && items_[i]->item == item && items_[i]->item->get_max_stack() > items_[i]->amount) {
			//여유공간이 얼마나 있는가
			int space = items_[i]->item->get_max_stack() - items_[i]->amount;
			
			items_[i]->amount += min(space, remain_amount);
			remain_amount -= min(space, remain_amount);
			//인벤토리 변경 이벤트 핸들러 실행
			for (int j = 0; j < item_handlers_.size(); j++) {
				item_handlers_[j].handler(this, i, items_[i], item_handlers_[j].args);
			}

			if(remain_amount <= 0)
				break;
		}
	}
	//2순위: 빈 자리
	if (remain_amount>0) {
		for (int i = 0; i < items_.size(); i++) {
			if (!items_[i]) {
				int space = item->get_max_stack();
				items_[i]= DEBUG_NEW ItemData{ item, min(space, remain_amount) };
				remain_amount -= min(space, remain_amount);
				//인벤토리 변경 이벤트 핸들러 실행
				for (int j = 0; j < item_handlers_.size(); j++) {
					item_handlers_[j].handler(this, i, items_[i], item_handlers_[j].args);
				}
				if (remain_amount <= 0) break;
			}
		}
	}

	//자리를 찾지 못했을 경우
	if (remain_amount > 0) return false;


	return true;
}

bool Inventory::ChangeItemPos(int index1, int index2)
{
	if (index1 >= 0 && items_.size() > index1 && index2 >= 0 && items_.size() > index2) {
		ItemData* tmp = items_[index1];
		items_[index1] = items_[index2];
		items_[index2] = tmp;

		//인벤토리 변경 이벤트 핸들러 실행
		for (int j = 0; j < item_handlers_.size(); j++) {
			item_handlers_[j].handler(this, index1, items_[index1], item_handlers_[j].args);
			item_handlers_[j].handler(this, index2, items_[index2], item_handlers_[j].args);
		}
	}

	return true;
}

bool Inventory::RemoveItem(int index, int amount)
{
	if (index >= 0 && items_.size() > index && items_[index]) {
		//갖고 있는 아이템의 수가 사용하려는 수보다 작으면 안 됨.
		if (items_[index]->amount >= amount) {

			const IItem* item = items_[index]->item;
			if (item) {
				items_[index]->amount = items_[index]->amount - amount;
				//	사용 후에 아이템이 0개가 됐을 경우. 인벤토리에서 삭제 처리.
				if (items_[index]->amount <= 0) {
					delete items_[index];
					items_[index] = nullptr;
				}
				//3. 인벤토리 변경 이벤트 핸들러 실행
				for (int i = 0; i < item_handlers_.size(); i++) {
					item_handlers_[i].handler(this, index, items_[index], item_handlers_[i].args);
				}
				return true;
			}
		}



	}
	return false;
}

const std::vector<ItemData*>& Inventory::GetItems()
{
	return items_;
}

bool Inventory::AddGold(UINT gold)
{
	gold_ += gold;

	for (const OnInventoryGoldChangedData& handler : gold_handlers_) {
		handler.handler(this, gold_, handler.args);
	}
	return true;
}

bool Inventory::RemoveGold(UINT gold)
{
	if (gold_ < gold) return false;
	
	gold_ -= gold;
	for (const OnInventoryGoldChangedData& handler : gold_handlers_) {
		handler.handler(this, gold_, handler.args);
	}
	return true;
}
