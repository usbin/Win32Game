#pragma once
#include "global.h"

class Player;
class IItem;
class ItemData;
class Inventory;


struct OnInventoryItemChangedArgs {
	DWORD_PTR sender;
	DWORD_PTR param;
};
typedef void (*OnInventoryItemChanged) (Inventory* inventory, int index, ItemData* new_data, OnInventoryItemChangedArgs args);
struct OnInventoryItemChangedData {
	OnInventoryItemChanged handler;
	OnInventoryItemChangedArgs args;
};

struct OnInventoryGoldChangedArgs {
	DWORD_PTR sender;
	DWORD_PTR param;
};
typedef void (*OnInventoryGoldChanged) (Inventory* inventory, UINT new_gold, OnInventoryGoldChangedArgs args);
struct OnInventoryGoldChangedData {
	OnInventoryGoldChanged handler;
	OnInventoryGoldChangedArgs args;
};

/// <summary>
/// Player가 소지함.
/// </summary>
class Inventory
{
public:
	~Inventory();
private:
	Player* owner_ = nullptr;
	UINT gold_ = 0;
	std::vector<ItemData*> items_;
	std::vector<OnInventoryItemChangedData> item_handlers_;
	std::vector<OnInventoryGoldChangedData> gold_handlers_;

public:
	void Init(Player* player);
	void AddTmpData();
	void AddItemHandler(OnInventoryItemChanged handler, OnInventoryItemChangedArgs args);
	void RemoveItemHandler(GObject* sender);
	void AddGoldHander(OnInventoryGoldChanged handler, OnInventoryGoldChangedArgs args);
	void RemoveGoldHandler(GObject* sender);
	
	const ItemData* GetItem(int index);
	const std::vector<ItemData*>& GetItems();

	//데이터 변경 함수(핸들러 실행하지 않음)
	bool AddGold(UINT gold);
	bool RemoveGold(UINT gold);
	//데이터 변경 함수(OnInventoryDataChanged 핸들러 실행)
	bool UseItem(int index, int amount);
	bool AddItem(const IItem* item, int amount);
	bool ChangeItemPos(int index1, int index2);
	bool RemoveItem(int index, int amount);


	

};

