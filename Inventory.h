#pragma once
#include "global.h"

class Player;
class IItem;
class ItemData;
class Inventory;


struct OnInventoryDataChangedArgs {
	DWORD_PTR sender;
	DWORD_PTR param;
};

typedef void (*OnInventoryDataChanged) (Inventory* inventory, int index, ItemData* new_data, OnInventoryDataChangedArgs args);


struct OnInventoryDataChangedData {
	OnInventoryDataChanged handler;
	OnInventoryDataChangedArgs args;
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
	std::vector<ItemData*> items_;
	std::vector<OnInventoryDataChangedData> handlers_;

public:
	void Init(Player* player);
	void AddHandler(OnInventoryDataChanged handler, OnInventoryDataChangedArgs args);
	
	const ItemData* GetItem(int index);
	const std::vector<ItemData*>& GetItems();

	//데이터 변경 함수
	bool UseItem(int index, int amount);
	bool AddItem(const IItem* item, int amount);
	bool ChangeItemPos(int index1, int index2);

	

};

