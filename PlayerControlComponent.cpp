#include "PlayerControlComponent.h"
#include "Player.h"
#include "Time.h"
#include "Collider.h"
#include "Animator.h"
#include "RealObjectSprite.h"
#include "IItemHolder.h"
#include "IUsable.h"

void PlayerControlComponent::Update(RealObject* obj)
{
	Player* player = dynamic_cast<Player*>(obj);
	if (player) {

		Vector2 v;
		float run_speed_2x = 2.f;
		Vector2 move_direction{ 0, 0 };
		float calculated_speed = player->speed_;

		if (KEY_HOLD(KEY::X)) {
			if (player->get_item_holder()) {
				const IItem* item = player->GetHoldItem();
				if (item) {
					const IUsable* usable_item = dynamic_cast<const IUsable*>(item);
					if (usable_item) {
						usable_item->Use(player);
					}
				}
			}
		}

		if (KEY_HOLD(KEY::UP)) {
			move_direction.y = -1;
			player->set_direction(DIRECTION::UP);
		}
		else if (KEY_HOLD(KEY::DOWN)) {
			move_direction.y = 1;
			player->set_direction(DIRECTION::DOWN);
		}
		if (KEY_HOLD(KEY::RIGHT)) {
			move_direction.x = 1;
			player->set_direction(DIRECTION::RIGHT);
		}
		else if (KEY_HOLD(KEY::LEFT)) {
			move_direction.x = -1;
			player->set_direction(DIRECTION::LEFT);
		}

		if (move_direction == Vector2{ 0, 0 }) {
			player->state_ = PLAYER_STATE::IDLE;
		}
		else if (KEY_HOLD(KEY::SHIFT)) {
			player->state_ = PLAYER_STATE::WALK;
		}
		else {
			player->state_ = PLAYER_STATE::RUN;
			calculated_speed*= run_speed_2x;
		}
		
		v.x = static_cast<float>(move_direction.Normalize().x * calculated_speed * Time::GetInstance()->dt_f());
		v.y = static_cast<float>(move_direction.Normalize().y * calculated_speed * Time::GetInstance()->dt_f());


		player->set_velocity(v);

		
	}
}
