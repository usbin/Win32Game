#include "PlayerControlComponent.h"
#include "Player.h"
#include "Time.h"
#include "Collider.h"
#include "Animator.h"
#include "RealObjectSprite.h"
#include "IItemHolder.h"
#include "IUsable.h"
#include "Game.h"
#include "Interactor.h"

void PlayerControlComponent::Update(RealObject* obj)
{
	Player* player = dynamic_cast<Player*>(obj);
	Vector2 v{ 0, 0 };
	if (player) {
		float run_speed_2x = 2.f;
		Vector2 move_direction{ 0, 0 };
		float calculated_speed = player->speed_;
		if( !CHECK_GAME_STATE(GAME_STATE_CONTROL_FREEZED) ){
		

			//아이템 사용: C
			if (KEY_HOLD(KEY::C) || KEY_HOLD(KEY::LBUTTON)) {
				if (player->get_item_holder() && player->get_item_holder()->GetItemData()) {
					player->get_item_holder()->UseItem();
				}
			}
			//아이템 상호작용: X
			if (KEY_HOLD(KEY::X) || KEY_HOLD(KEY::RBUTTON)) {
				if (player->get_interactor()) {
					const std::vector<Interactor*>& interactors = player->get_interactor()->get_interactors();
					if (!interactors.empty()) {
						interactors[0]->OnInteract(player);
					}
				}
			}

			if (KEY_HOLD(KEY::W)) {
				move_direction.y = -1;
				player->set_direction(DIRECTION::UP);
				
			}
			else if (KEY_HOLD(KEY::S)) {
				move_direction.y = 1;
				player->set_direction(DIRECTION::DOWN);
			}
			if (KEY_HOLD(KEY::D)) {
				move_direction.x = 1;
				player->set_direction(DIRECTION::RIGHT);
			}
			else if (KEY_HOLD(KEY::A)) {
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
				calculated_speed *= run_speed_2x;
			}

			v.x = static_cast<float>(move_direction.Normalize().x * calculated_speed * Time::GetInstance()->dt_f());
			v.y = static_cast<float>(move_direction.Normalize().y * calculated_speed * Time::GetInstance()->dt_f());


		}
		else {
			player->state_ = PLAYER_STATE::IDLE;

		}


		player->set_velocity(v);
		
	}
}
