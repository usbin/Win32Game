#include "ItemLooter.h"
#include "Player.h"
#include "SceneManager.h"
#include "Time.h"
#include "Collider.h"
#include "DropItem.h"
#include "Inventory.h"
#include "IItem.h"
void ItemLooter::Init(Player* player, Vector2 pos_offset)
{
	owner_ = player;
	pos_offset_ = pos_offset;
}

void ItemLooter::Update()
{
	if (owner_ && owner_->IsDead()) owner_ = nullptr;

	if (owner_) {
		//owner_의 위치에서 최소 반경<아이템<최대반경 인 아이템을 모두 끌어당김.
		//owner_의 위치에서 아이템<최소반경 인 아이템을 루팅함.
		const std::vector<GObject*>& drop_items = SceneManager::GetInstance()->get_current_scene()->GetGroupObjects(GROUP_TYPE::DROP_ITEM);
		for (int i = 0; i < drop_items.size(); i++) {
			Vector2 item_pos = drop_items[i]->get_pos();
			Vector2 player_pos = owner_->get_pos() + pos_offset_;
			// d <= 작은 반지름 + 큰 반지름 이면 서로 만남.
			// 반지름... scale.x, scale.y의 평균값을 2로 나누자.
			float item_r = (drop_items[i]->get_scale().x + drop_items[i]->get_scale().y) / 4.f;
			float player_r = (owner_->get_scale().x + owner_->get_scale().y) / 4.f;
			float distance = sqrt(pow(item_pos.x - player_pos.x, 2) + pow(item_pos.y - player_pos.y, 2));

			//반경 내에 있음!
			if (distance <= item_r + player_r + LOOT_RANGE) {
				DropItem* item = dynamic_cast<DropItem*>(drop_items[i]);

				item ->SetLooter(this);
				
			}

		}
	}
}

bool ItemLooter::Loot(const IItem* item, UINT amount)
{
	//인벤에 추가
	if (owner_->get_inventory())
		return owner_->get_inventory()->AddItem(item, amount);
	else return false;

}

inline Vector2 ItemLooter::get_pos()
{
	if (owner_) {
		return owner_->get_pos() + pos_offset_;
	}
	else return Vector2();
}
