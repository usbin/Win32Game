#include "PhysicsComponent.h"
#include "RealObject.h"
#include "Collider.h"
PhysicsComponent::PhysicsComponent()
{
}
PhysicsComponent::~PhysicsComponent()
{
}
void PhysicsComponent::FinalUpdate(RealObject* obj)
{
	const std::vector<Collider*> collisions = obj->get_collider()->get_physical_collisions();
	Vector2 calculated_v = obj->get_velocity();
	if (!collisions.empty()) {
		//�浹���� �� -> ��� collider ���������� velocity�� 0���� ������ �� ����.
		for (int i = 0; i < collisions.size(); i++) {

			Vector2 pos_differency =  obj->get_collider()->get_pos() - collisions[i]->get_pos();
			//�з������ϴ� ����
			Vector2 direction{ pos_differency.x / abs(pos_differency.x), pos_differency.y / abs(pos_differency.y) };

			// ���� ��ġ�� ���� (0���� ������ ��ġ�� �ʴ� ��)
			Vector2 overlapped =
				obj->get_collider()->get_pos() - direction * obj->get_collider()->get_scale() / 2.f - (collisions[i]->get_pos() + collisions[i]->get_scale() / 2.f * direction);
			
			overlapped = overlapped*direction*-1;

			if (overlapped.x > 0 && overlapped.y > 0) {
				overlapped = Vector2{ max(overlapped.x, 0), max(overlapped.y, 0) };
				//�� ���� ��ģ ������ �о.
				//��, 0�� ���� ���� ��ġ�� ���� ���̹Ƿ� ������.
				//=0�� �ƴϸ鼭 �� ���� ��.

				if (overlapped.y == 0 || (overlapped.x < overlapped.y && overlapped.x > 0)) {

					calculated_v.x = (overlapped.x + 1)*direction.x;
					calculated_v.y = 0;
				}
				else if (overlapped.x == 0 || (overlapped.y < overlapped.x && overlapped.y > 0)) {

					calculated_v.y = (overlapped.y + 1)*direction.y;
					calculated_v.x = 0;
				}
			}
			
		}
	}
	obj->set_pos(obj->get_pos()+calculated_v);

}