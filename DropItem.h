#pragma once
#include "global.h"
#include "RealObject.h"
class IItem;
class ItemLooter;


/// <summary>
/// 바닥에 떨어져 다가가면 루팅되는 상태의 아이템
/// </summary>


class DropItem : public RealObject
{

private:
	const IItem* item_ = nullptr;
	UINT amount_ = 0;

	ItemLooter* looter_ = nullptr;//주운 플레이어의 루터.

	void CreateRenderCmp();
public:
	void Init(const IItem* item, UINT amount);
	void Update() override;
	void SetLooter(ItemLooter* looter);	//한 번 설정된 Looter에게 n초 안에 무조건 주워짐.

	inline const IItem* get_item() { return item_; };
	inline UINT get_amount() { return amount_; };
};

