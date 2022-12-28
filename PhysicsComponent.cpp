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
		//충돌했을 때 -> 상대 collider 방향으로의 velocity를 0으로 설정한 후 적용.
		for (int i = 0; i < collisions.size(); i++) {
			Vector2 pos_differency = collisions[i]->get_pos() - obj->get_pos();
			//곱했을 때 양수이면 해당 콜라이더가 있는 방향으로 오브젝트가 진행하는 것. 진행방향 반대로 1픽셀 튕겨냄.
			if (pos_differency.x * obj->velocity_.x > 0) {
				obj->velocity_.x = -1 * obj->velocity_.x / abs(obj->velocity_.x);
			}
			if (pos_differency.y * obj->velocity_.y > 0) {
				obj->velocity_.y = -1 * obj->velocity_.y / abs(obj->velocity_.y);
			}
		}
	}

	obj->set_pos(obj->get_pos() + obj->velocity_);

}