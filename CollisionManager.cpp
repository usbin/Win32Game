#include "CollisionManager.h"
#include "GObject.h"
#include "RealObject.h"
#include "SceneManager.h"
#include "Collider.h"

CollisionManager::CollisionManager() {}
CollisionManager::~CollisionManager() {}

void CollisionManager::Init()
{
	//Player-Monster
	CheckGroupBitmap(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	//Missile-Monster
	CheckGroupBitmap(GROUP_TYPE::MISSILE, GROUP_TYPE::MONSTER);
	//Interactor-Interactor
	CheckGroupBitmap(GROUP_TYPE::INTERACTOR, GROUP_TYPE::INTERACTOR);

	CheckGroupBitmap(GROUP_TYPE::PLAYER, GROUP_TYPE::INVISIBLE_WALL);
	CheckGroupBitmap(GROUP_TYPE::PLAYER, GROUP_TYPE::SHIPPING_BOX);
}

void CollisionManager::Update()
{
	//���� ���� ��� ������Ʈ�� �ݸ����� �޾ƿ;���.
	//(1)�浹 ������ �׷��� ��Ʈ�� 32x32 => Init���� �������ٰ���.
	//(2)��Ʈ���� ��ȸ�ϸ� ���� ���� �ش� �׷�A, �׷�B ������Ʈ ����Ʈ�� �޾ƿ�.
	//(3)�� �׷��� �浹 ���� üũ
	// - (i) ������ �浹���� �ʾҰ� ���� �浹���� -> OnCollisionEnter
	// - (ii) ������ �浹�߰� ���ݵ� �浹�� -> OnCollisionStay
	// - (iii) ������ �浹�߰� ������ �浹���� ���� -> OnCollisionExit
	for (UINT i = 0; i < static_cast<UINT>(GROUP_TYPE::END); i++) {
		for (UINT j = i; j < static_cast<UINT>(GROUP_TYPE::END); j++) {
			// �� �׷��� �浹���ΰ� üũ������ ������ + �Ѵ� UI�� �ƴ� ������
			if (static_cast<GROUP_TYPE>(i) != GROUP_TYPE::UI
				&& static_cast<GROUP_TYPE>(j) != GROUP_TYPE::UI
				&&
				group_collision_bitmap_[i] & (1 << j)) {
				const std::vector<GObject*>& group1_objs = SceneManager::GetInstance()->get_current_scene()->GetGroupObjects(static_cast<GROUP_TYPE>(i));
				const std::vector<GObject*>& group2_objs = SceneManager::GetInstance()->get_current_scene()->GetGroupObjects(static_cast<GROUP_TYPE>(j));
				GroupObjectCollision(group1_objs, group2_objs);
			}
			
		}
	}
	
}

void CollisionManager::CheckGroupBitmap(GROUP_TYPE group1, GROUP_TYPE group2)
{
	// ��Ʈ������ [0,1]�� [1,0]�� �ǹ��ϴ� �� �����Ƿ�(0�� �׷�� 1�� �׷��� �浹����)
	// �밢�� ���ݸ� �����.
	// ������ ���� �׷��� ������ ���̰� ��. ( [0,1]�� ����ϰ� [1,0]�� ������� ���� )
	UINT row = static_cast<UINT>(group1);
	UINT col = static_cast<UINT>(group2);
	if (row > col) {
		col = static_cast<UINT>(group1);
		row = static_cast<UINT>(group2);
	}

	group_collision_bitmap_[row] |= 1 << col;

}

void CollisionManager::GroupObjectCollision(const std::vector<GObject*>& group1_objs, const std::vector<GObject*>& group2_objs)
{
	for (int i = 0; i < group1_objs.size(); i++) {
		RealObject* obj1 = static_cast<RealObject*>(group1_objs[i]);

		if (obj1->get_collider() == nullptr) continue; //�ϳ��� �ݶ��̴��� ������ �浹x

		for (int j = 0; j < group2_objs.size(); j++) {
			RealObject* obj2 = static_cast<RealObject*>(group2_objs[j]);
			
			if (obj2->get_collider() == nullptr) continue; //�ϳ��� �ݶ��̴��� ������ �浹x
			if (obj1 == obj2) continue; //���� ������Ʈ������ �浹x


			// ���� �浹 ���η� �з��ؼ� Collider �ݹ��Լ� ����
			// �� ���� ���� ù��° ���̵�� ������
			UINT cid1 = obj1->get_collider()->get_id();
			UINT cid2 = obj2->get_collider()->get_id();
			if (cid1 > cid2) {
				cid1 = obj2->get_collider()->get_id();
				cid2 = obj1->get_collider()->get_id();
			}
			CollisionId cls_id;
			cls_id.collider1_id = cid1;
			cls_id.collider2_id = cid2;
			auto it = prev_collision_.find(cls_id.Id);

			if (it == prev_collision_.end()) {
				prev_collision_.insert(std::make_pair(cls_id.Id, false));
				it = prev_collision_.find(CollisionId{ cid1, cid2 }.Id);
			}

			//�浹�� ���
			if (IsCollision(obj1, obj2)) {

				//(1) FALSE�� -> ���� �浹��.
				if (!it->second) {
					// �Ѵ� ���� ������ �ƴ� ������
					if (!obj1->IsDead() && !obj2->IsDead()) {
						prev_collision_.insert(std::make_pair(cls_id.Id, true));
						obj1->get_collider()->OnCollisionEnter(obj2->get_collider());
						obj2->get_collider()->OnCollisionEnter(obj1->get_collider());

						it->second = true;
					}
					//�ϳ��� ���� �����̸� �ƹ� ó��x
				}

				//(2) TRUE�� -> �浹����
				else{
					//�Ѵ� ���� ������ �ƴ� ������
					if (!obj1->IsDead() && !obj2->IsDead()) {
						obj1->get_collider()->OnCollisionStay(obj2->get_collider());
						obj2->get_collider()->OnCollisionStay(obj1->get_collider());

						it->second = true;
					}
					//�ϳ��� ���� �����̸� �ڿ������� Exit ó��
					else {
						obj1->get_collider()->OnCollisionExit(obj2->get_collider());
						obj2->get_collider()->OnCollisionExit(obj1->get_collider());

						it->second = false;
					}

				}

			}
			//�浹�� �ƴ� ���
			else {
				//(3) TRUE�� -> �浹���� ��������.
				if (it->second) {
					obj1->get_collider()->OnCollisionExit(obj2->get_collider());
					obj2->get_collider()->OnCollisionExit(obj1->get_collider());
				}
				it->second = false;
			}
		}
	}
}

bool CollisionManager::IsCollision(RealObject* obj1, RealObject* obj2)
{
	//�浹 ����: obj1�� obj2�� ������ ��ģ��.
	// = x��ǥ�� �Ÿ��� ���� ���� ������ ���� ���ݺ��� �۰�
	//	 y��ǥ�� �Ÿ��� ���� ���� ������ ���� ���ݺ��� �۴�
	Collider* c1 = obj1->get_collider();
	Collider* c2 = obj2->get_collider();
	
	return
		abs(c1->get_pos().x - c2->get_pos().x) < ((c1->get_scale().x + c2->get_scale().x) / 2)
		&& abs(c1->get_pos().y - c2->get_pos().y) < ((c1->get_scale().y + c2->get_scale().y) / 2);
}

void CollisionManager::ResetGroupBitmap()
{
	memset(group_collision_bitmap_, 0, sizeof(group_collision_bitmap_));
}
