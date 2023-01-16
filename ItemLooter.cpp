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
		//owner_�� ��ġ���� �ּ� �ݰ�<������<�ִ�ݰ� �� �������� ��� ������.
		//owner_�� ��ġ���� ������<�ּҹݰ� �� �������� ������.
		const std::vector<GObject*>& drop_items = SceneManager::GetInstance()->get_current_scene()->GetGroupObjects(GROUP_TYPE::DROP_ITEM);
		for (int i = 0; i < drop_items.size(); i++) {
			Vector2 item_pos = drop_items[i]->get_pos();
			Vector2 player_pos = owner_->get_pos() + pos_offset_;
			// d <= ���� ������ + ū ������ �̸� ���� ����.
			// ������... scale.x, scale.y�� ��հ��� 2�� ������.
			float item_r = (drop_items[i]->get_scale().x + drop_items[i]->get_scale().y) / 4.f;
			float player_r = (owner_->get_scale().x + owner_->get_scale().y) / 4.f;
			float distance = sqrt(pow(item_pos.x - player_pos.x, 2) + pow(item_pos.y - player_pos.y, 2));

			//�ݰ� ���� ����!
			if (distance <= item_r + player_r + LOOT_RANGE) {
				DropItem* item = dynamic_cast<DropItem*>(drop_items[i]);

				item ->SetLooter(this);
				
			}

		}
	}
}

bool ItemLooter::Loot(const IItem* item, UINT amount)
{
	//�κ��� �߰�
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
