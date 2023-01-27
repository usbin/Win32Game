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
#include "FmodSound.h"
#include "ResManager.h"

void PlayerControlComponent::Update(RealObject* obj)
{
	Player* player = dynamic_cast<Player*>(obj);
	Vector2 v{ 0, 0 };
	if (player && !player->IsDead()) {
		float run_speed_2x = 2.f;
		Vector2 move_direction{ 0, 0 };
		float calculated_speed = player->speed_;
		if( !CHECK_GAME_STATE(GAME_STATE_CONTROL_FREEZED) ){
		

			
			//������ ���: C
			if (KEY_HOLD(KEY::C) || KEY_HOLD(KEY::LBUTTON)) {
				if (player->get_item_holder() && player->get_item_holder()->GetItemData()) {

					//���콺 �������� ĳ���� ���� ��ȯ
					if (KEY_HOLD(KEY::LBUTTON)) {
						//x�� ����, �ش� �������� ����
						Vector2 xy{ GET_MOUSE_POS() - (player->get_collider()->get_pos_offset()+player->get_pos())};
						xy.y *= -1;//y�� ����(��ǥ���� ���߱�)
						float radian = atan2(xy.y, xy.x);
						//atan2�� 3�ù����� 0��, �ݽð�������� 180��, �ð�������� -180��
						//degree�� radian*180/Math.PI
						int degree = radian * 180.f / std::acos(-1);

						if (degree > 45 && degree < 90 + 45) {
							player->set_direction(DIRECTION::UP);
						}
						else if ((degree > (90 + 45) && degree < 180)
							||(degree<-90 - 45 && degree > -180)) {
							player->set_direction(DIRECTION::LEFT);
						}
						else if (degree>(-90-45) && degree< -45) {
							player->set_direction(DIRECTION::DOWN);
						}
						else if ((degree > 0 && degree < 45)
							|| (degree<0 && degree>-45)) {
							player->set_direction(DIRECTION::RIGHT);
						}
						player->get_item_holder()->Update();
						//degree+45 / 90 �� 0�� �� ->��
						//1�� �� -> ��
						//2�� �� -> ��
						//3�� �� -> ��

					}

					player->get_item_holder()->UseItem();
				}
			}
			//������ ��ȣ�ۿ�: X
			if (KEY_HOLD(KEY::X) || KEY_HOLD(KEY::RBUTTON)) {
				if (player->get_interactor()) {
					const std::vector<Interactor*>& interactors = player->get_interactor()->get_interactors();
					if (!interactors.empty()) {
						interactors[0]->OnInteract(player);
					}
				}
			}

			Sound* sound = ResManager::GetInstance()->LoadSound(_T("FarmStep Effect"), _T("sound\\FarmStep_Effect.wav"));

			if (KEY_HOLD(KEY::W)) {
				move_direction.y = -1;
				player->set_direction(DIRECTION::UP);

				FmodSound::GetInstance()->PlayStep(sound);
			}
			else if (KEY_HOLD(KEY::S)) {
				move_direction.y = 1;
				player->set_direction(DIRECTION::DOWN);
				FmodSound::GetInstance()->PlayStep(sound);
			}
			if (KEY_HOLD(KEY::D)) {
				move_direction.x = 1;
				player->set_direction(DIRECTION::RIGHT);
				FmodSound::GetInstance()->PlayStep(sound);
			}
			else if (KEY_HOLD(KEY::A)) {
				move_direction.x = -1;
				player->set_direction(DIRECTION::LEFT);
				FmodSound::GetInstance()->PlayStep(sound);
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
