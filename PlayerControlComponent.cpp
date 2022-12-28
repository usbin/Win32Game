#include "PlayerControlComponent.h"
#include "Player.h"
#include "Time.h"
#include "Collider.h"
void PlayerControlComponent::Update(RealObject* obj)
{
	Player* player = dynamic_cast<Player*>(obj);
	if (player) {

		Vector2 v;

		Vector2 move_direction{ 0, 0 };
		if (KEY_HOLD(KEY::RIGHT)) {
			move_direction.x = 1;
			player->set_direction(DIRECTION::RIGHT);
		}
		else if (KEY_HOLD(KEY::LEFT)) {
			move_direction.x = -1;
			player->set_direction(DIRECTION::LEFT);
		}
		if (KEY_HOLD(KEY::UP)) {
			move_direction.y = -1;
		}
		else if (KEY_HOLD(KEY::DOWN)) {
			move_direction.y = 1;
		}

		
		v.x = static_cast<float>(move_direction.Normalize().x * player->speed_ * Time::GetInstance()->dt_f());
		v.y = static_cast<float>(move_direction.Normalize().y * player->speed_ * Time::GetInstance()->dt_f());

		player->set_velocity(v);
		
	}
}
