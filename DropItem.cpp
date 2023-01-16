#include "DropItem.h"
#include "DropItemRenderComponent.h"
#include "IItem.h"
#include "ItemLooter.h"
#include "Time.h"
void DropItem::CreateRenderCmp()
{
	render_cmp_ = new DropItemRenderComponent(this);
}

void DropItem::Init(const IItem* item, UINT amount)
{
	item_ = item;
	amount_ = amount;
	CreateRenderCmp();
}

void DropItem::Update()
{

	if (looter_) {
		//루터를 따라감.
		//플레이어 방향으로 이동
		// atan(y거리/x거리) = 세타

		Vector2 item_pos = get_pos();
		Vector2 looter_pos = looter_->get_pos();
		float distance = sqrt(pow(item_pos.x - looter_pos.x, 2) + pow(item_pos.y - looter_pos.y, 2));

		//일정 이상 가까워지면 획득
		if (distance <= 24.f) {
			if (looter_->Loot(item_, amount_)) {
				DeleteGObject(this, GROUP_TYPE::DROP_ITEM);
				return;
			}
		}
		float angle = atan2((item_pos.y - looter_pos.y), (item_pos.x - looter_pos.x));
		float x = Time::GetInstance()->dt_f() * 6.f * distance * cos(angle);
		float y = Time::GetInstance()->dt_f() * 6.f * distance * sin(angle);
		set_pos(Vector2{ item_pos.x - x, item_pos.y - y });
	}
	

}

void DropItem::SetLooter(ItemLooter* looter)
{
	if(!looter_)
		looter_ = looter;
}
