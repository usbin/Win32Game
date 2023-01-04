#pragma once
#include "global.h"
class RealObject;
class ItemSprite;

/// <summary>
/// �����͸� �����ϱ� ���� ��ü�̹Ƿ� Init�� �����ϰ� ��� �Լ��� const���� ��.
/// </summary>
class IItem
{
public:
	virtual ~IItem() = 0 {};
	virtual IItem* Init(int item_code, tstring name) = 0;	
	virtual void OnHold(RealObject* owner) const = 0;					//�������� ������� �� ����
	virtual int get_item_code() const = 0;
	virtual ItemSprite* get_sprite() const = 0;

};

struct ItemData {
	const IItem* item;
	int amount;
};