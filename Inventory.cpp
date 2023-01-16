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
		//���� �ִ� �������� ���� ����Ϸ��� ������ ������ �� ��.
		if (items_[index]->amount >= amount) {

			const IItem* item = items_[index]->item;
			if (item) {
				//������ ��� ó��
				//1. ��� ������ �������� ��� ��� �Լ� ����.
				const IUsable* usable_item = dynamic_cast<const IUsable*>(item);
				if (usable_item) {
					if (usable_item->Use(owner_)) {
						//2. ��� �������̸� ����ص� ���� �پ���� ����.
						//	�� ���� ��� ����ϸ� ���� �پ��.
						if (!dynamic_cast<const Equip*>(items_[index]->item)) {
							items_[index]->amount = items_[index]->amount - amount;
						}
						//	��� �Ŀ� �������� 0���� ���� ���. �κ��丮���� ���� ó��.
						if (items_[index]->amount <= 0) {
							delete items_[index];
							items_[index] = nullptr;
						}
						//3. �κ��丮 ���� �̺�Ʈ �ڵ鷯 ����
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
	//���� �ڸ� ã��
	//1����: ������ ���� ���� ���� ���� ������
	int result_i = items_.size();
	for (int i = 0; i < items_.size(); i++) {
		if (items_[i] && items_[i]->item == item && items_[i]->item->get_max_stack() >= amount + items_[i]->amount) {
			result_i = i;
			break;
		}
	}
	//2����: �� �ڸ�
	if (result_i >= items_.size()) {
		for (int i = 0; i < items_.size(); i++) {
			if (!items_[i]) {
				result_i = i;
				break;
			}
		}
	}

	//�ڸ��� ã�� ������ ���.
	if (result_i >= items_.size()) return false;
	


	//ã�� �ڸ��� �� ĭ�� ���
	if (!items_[result_i]) {
		items_[result_i] = DEBUG_NEW ItemData{ item, amount };

	}
	//3.ã�� �ڸ��� �̹� �������� ������ ���
	else {
		items_[result_i]->amount += amount;
	}

	//�κ��丮 ���� �̺�Ʈ �ڵ鷯 ����
	for (int j = 0; j < handlers_.size(); j++) {
		handlers_[j].handler(this, result_i, items_[result_i], handlers_[j].args);
	}
	return true;
}

const std::vector<ItemData*>& Inventory::GetItems()
{
	return items_;
}
