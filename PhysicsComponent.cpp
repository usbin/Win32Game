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
		//충돌했을 때 -> 상대 collider 방향으로의 velocity를 0으로 설정한 후 적용.
		for (int i = 0; i < collisions.size(); i++) {

			Vector2 pos_differency =  obj->get_collider()->get_pos() - collisions[i]->get_pos();
			//밀려나야하는 방향
			Vector2 direction{ pos_differency.x / abs(pos_differency.x), pos_differency.y / abs(pos_differency.y) };

			// 현재 겹치는 정도 (0보다 작으면 겹치지 않는 것)
			Vector2 overlapped =
				obj->get_collider()->get_pos() - direction * obj->get_collider()->get_scale() / 2.f - (collisions[i]->get_pos() + collisions[i]->get_scale() / 2.f * direction);
			
			overlapped = overlapped*direction*-1;

			if (overlapped.x > 0 && overlapped.y > 0) {
				overlapped = Vector2{ max(overlapped.x, 0), max(overlapped.y, 0) };
				//더 조금 겹친 쪽으로 밀어냄.
				//단, 0일 경우는 전혀 겹치지 않은 것이므로 제외함.
				//=0이 아니면서 더 작은 값.

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