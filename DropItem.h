#pragma once
#include "global.h"
#include "RealObject.h"
class IItem;
class ItemLooter;


/// <summary>
/// �ٴڿ� ������ �ٰ����� ���õǴ� ������ ������
/// </summary>


class DropItem : public RealObject
{

private:
	const IItem* item_ = nullptr;
	UINT amount_ = 0;

	ItemLooter* looter_ = nullptr;//�ֿ� �÷��̾��� ����.

	void CreateRenderCmp();
public:
	void Init(const IItem* item, UINT amount);
	void Update() override;
	void SetLooter(ItemLooter* looter);	//�� �� ������ Looter���� n�� �ȿ� ������ �ֿ���.

	inline const IItem* get_item() { return item_; };
	inline UINT get_amount() { return amount_; };
};

