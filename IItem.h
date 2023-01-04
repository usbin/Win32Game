#pragma once
#include "global.h"
class RealObject;
class ItemSprite;

/// <summary>
/// 데이터를 참조하기 위한 객체이므로 Init을 제외하고 모든 함수가 const여야 함.
/// </summary>
class IItem
{
public:
	virtual ~IItem() = 0 {};
	virtual IItem* Init(int item_code, tstring name) = 0;	
	virtual void OnHold(RealObject* owner) const = 0;					//아이템을 들고있을 때 동작
	virtual int get_item_code() const = 0;
	virtual ItemSprite* get_sprite() const = 0;

};

struct ItemData {
	const IItem* item;
	int amount;
};