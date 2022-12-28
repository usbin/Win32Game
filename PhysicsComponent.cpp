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
	if (!collisions.empty()) {
		//�浹���� �� -> ��� collider ���������� velocity�� 0���� ������ �� ����.
		for (int i = 0; i < collisions.size(); i++) {
			Vector2 pos_differency = collisions[i]->get_pos() - obj->get_pos();
			//������ �� ����̸� �ش� �ݶ��̴��� �ִ� �������� ������Ʈ�� �����ϴ� ��.
			if (pos_differency.x * obj->velocity_.x > 0) {
				obj->velocity_.x = 0;
			}
			if (pos_differency.y * obj->velocity_.y > 0) {
				obj->velocity_.y = 0;
			}
		}
	}

	obj->set_pos(obj->get_pos() + obj->velocity_);

}