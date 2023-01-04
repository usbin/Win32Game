#include "PlayerRenderComponent.h"
#include "Player.h"
#include "RealObjectSprite.h"
#include "RealObjectAnimator.h"
#include "ResManager.h"
#include "RealObjectSprite.h"
#include "RealObjectAnimator.h"
#include "GObjectSprite.h"

PlayerRenderComponent::PlayerRenderComponent(GObject* owner)
{
	

	owner_ = dynamic_cast<RealObject*>( owner );

	Texture* texture = ResManager::GetInstance()->LoadTexture(_T("player"), _T("texture\\StardewValley_Player.png"));
	RealObjectSprite* sprite_front = DEBUG_NEW RealObjectSprite();
	RealObjectSprite* sprite_back = DEBUG_NEW RealObjectSprite();
	RealObjectSprite* sprite_right = DEBUG_NEW RealObjectSprite();
	RealObjectSprite* sprite_left = DEBUG_NEW RealObjectSprite();
	RealObjectSprite* sprite_hold_front = DEBUG_NEW RealObjectSprite();
	RealObjectSprite* sprite_hold_back = DEBUG_NEW RealObjectSprite();
	RealObjectSprite* sprite_hold_right = DEBUG_NEW RealObjectSprite();
	RealObjectSprite* sprite_hold_left = DEBUG_NEW RealObjectSprite();
	sprite_front->QuickSet(texture, owner, Vector2{ 0, 0 }, Vector2{ 16, 32 });
	sprite_back->QuickSet(texture, owner, Vector2{ 0, 64 }, Vector2{ 16, 32 });
	sprite_right->QuickSet(texture, owner, Vector2{ 0, 32 }, Vector2{ 16, 32 });
	sprite_left->QuickSet(texture, owner, Vector2{ 0, 32 }, Vector2{ 16, 32 });
	sprite_hold_front->QuickSet(texture, owner, Vector2{ 112, 0 }, Vector2{ 16, 32 });
	sprite_hold_back->QuickSet(texture, owner, Vector2{ 112, 64 }, Vector2{ 16, 32 });
	sprite_hold_right->QuickSet(texture, owner, Vector2{ 112, 32 }, Vector2{ 16, 32 });
	sprite_hold_left->QuickSet(texture, owner, Vector2{ 112, 32 }, Vector2{ 16, 32 });
	sprites[(int)DIRECTION::UP][(int)PLAYER_STATE::IDLE][(int)PLAYER_HAND_STATE::NONE] = sprite_back;
	sprites[(int)DIRECTION::RIGHT][(int)PLAYER_STATE::IDLE][(int)PLAYER_HAND_STATE::NONE] = sprite_right;
	sprites[(int)DIRECTION::LEFT][(int)PLAYER_STATE::IDLE][(int)PLAYER_HAND_STATE::NONE] = sprite_left;
	sprites[(int)DIRECTION::DOWN][(int)PLAYER_STATE::IDLE][(int)PLAYER_HAND_STATE::NONE] = sprite_front;
	sprites[(int)DIRECTION::UP][(int)PLAYER_STATE::IDLE][(int)PLAYER_HAND_STATE::HOLD] = sprite_hold_back;
	sprites[(int)DIRECTION::RIGHT][(int)PLAYER_STATE::IDLE][(int)PLAYER_HAND_STATE::HOLD] = sprite_hold_right;
	sprites[(int)DIRECTION::LEFT][(int)PLAYER_STATE::IDLE][(int)PLAYER_HAND_STATE::HOLD] = sprite_hold_left;
	sprites[(int)DIRECTION::DOWN][(int)PLAYER_STATE::IDLE][(int)PLAYER_HAND_STATE::HOLD] = sprite_hold_front;

	CreateAnimator();

}

PlayerRenderComponent::~PlayerRenderComponent()
{
	for (int i = 0; i < (int)DIRECTION::END; i++) {
		for (int j = 0; j < (int)PLAYER_STATE::END; j++) {
			for (int k = 0; k < (int)PLAYER_HAND_STATE::END; k++) {
				if (sprites[i][j][k]) {
					delete sprites[i][j][k];
					sprites[i][j][k] = nullptr;
				}
			}
			
		}
	}
	delete animator_;
	delete sprite_;
}

void PlayerRenderComponent::CreateAnimator()
{
	Animator* old_animator = get_animator();
	if (old_animator) delete old_animator;

	Texture* texture = ResManager::GetInstance()->LoadTexture(_T("player"), _T("texture\\StardewValley_Player.png"));
	RealObjectAnimator* animator = DEBUG_NEW RealObjectAnimator();
	animator->CreateAnimation(
		_T("Walk_Front")
		, texture
		, Vector2{ 16, 0 }
		, Vector2{ 16, 32 }
		, Vector2{ 16, 0 }
		, Vector2{ 0, 0 }
		, .2f
		, 3
		, false);
	animation_names[(int)DIRECTION::DOWN][(int)PLAYER_STATE::WALK][(int)PLAYER_HAND_STATE::NONE] = _T("Walk_Front");
	animator->CreateAnimation(
		_T("Walk_Back")
		, texture
		, Vector2{ 16, 64 }
		, Vector2{ 16, 32 }
		, Vector2{ 16, 0 }
		, Vector2{ 0, 0 }
		, .2f
		, 3
		, false);
	animation_names[(int)DIRECTION::UP][(int)PLAYER_STATE::WALK][(int)PLAYER_HAND_STATE::NONE] = _T("Walk_Back");
	animator->CreateAnimation(
		_T("Walk_Right")
		, texture
		, Vector2{ 16, 32 }
		, Vector2{ 16, 32 }
		, Vector2{ 16, 0 }
		, Vector2{ 0, 0 }
		, .2f
		, 3
		, false);
	animation_names[(int)DIRECTION::RIGHT][(int)PLAYER_STATE::WALK][(int)PLAYER_HAND_STATE::NONE] = _T("Walk_Right");
	animator->CreateAnimation(
		_T("Walk_Left")
		, texture
		, Vector2{ 16, 32 }
		, Vector2{ 16, 32 }
		, Vector2{ 16, 0 }
		, Vector2{ 0, 0 }
		, .2f
		, 3
		, false);
	animation_names[(int)DIRECTION::LEFT][(int)PLAYER_STATE::WALK][(int)PLAYER_HAND_STATE::NONE] = _T("Walk_Left");
	animator->CreateAnimation(
		_T("Hold_And_Walk_Front")
		, texture
		, Vector2{ 112, 0 }
		, Vector2{ 16, 32 }
		, Vector2{ 16, 0 }
		, Vector2{ 0, 0 }
		, .2f
		, 3
		, false);
	animation_names[(int)DIRECTION::DOWN][(int)PLAYER_STATE::WALK][(int)PLAYER_HAND_STATE::HOLD] = _T("Hold_And_Walk_Front");
	animator->CreateAnimation(
		_T("Hold_And_Walk_Back")
		, texture
		, Vector2{ 112, 64 }
		, Vector2{ 16, 32 }
		, Vector2{ 16, 0 }
		, Vector2{ 0, 0 }
		, .2f
		, 3
		, false);
	animation_names[(int)DIRECTION::UP][(int)PLAYER_STATE::WALK][(int)PLAYER_HAND_STATE::HOLD] = _T("Hold_And_Walk_Back");
	animator->CreateAnimation(
		_T("Hold_And_Walk_Right")
		, texture
		, Vector2{ 112, 32 }
		, Vector2{ 16, 32 }
		, Vector2{ 16, 0 }
		, Vector2{ 0, 0 }
		, .2f
		, 3
		, false);
	animation_names[(int)DIRECTION::RIGHT][(int)PLAYER_STATE::WALK][(int)PLAYER_HAND_STATE::HOLD] = _T("Hold_And_Walk_Right");
	animator->CreateAnimation(
		_T("Hold_And_Walk_Left")
		, texture
		, Vector2{ 112, 32 }
		, Vector2{ 16, 32 }
		, Vector2{ 16, 0 }
		, Vector2{ 0, 0 }
		, .2f
		, 3
		, false);
	animation_names[(int)DIRECTION::LEFT][(int)PLAYER_STATE::WALK][(int)PLAYER_HAND_STATE::HOLD] = _T("Hold_And_Walk_Left");

	animator->set_owner(get_owner());
	set_animator(animator);
}

void PlayerRenderComponent::Update(GObject* owner)
{

	animator_->Update();

	Player* player = dynamic_cast<Player*>(owner);

	if (player) {
		switch (player->state_) {
		case PLAYER_STATE::IDLE: {
			if (animator_) animator_->Stop();
			ISprite* new_sprite = sprites[(int)player->get_direction()][(int)player->state_][(int)player->hand_state_];
			if (sprite_
				&&sprite_->get_texture() == new_sprite->get_texture()
				&& sprite_->get_base_pos() == new_sprite->get_base_pos()
				&& sprite_->get_scale() == new_sprite->get_scale()) {
				//아무것도 하지않음
			}
			else {
				ChangeSprite(DEBUG_NEW RealObjectSprite(*dynamic_cast<RealObjectSprite*>(new_sprite)));
			}
		} break;
		case PLAYER_STATE::WALK: {
			if (!animator_->is_current_playing(animation_names[(int)player->get_direction()][(int)player->state_][(int)player->hand_state_]))
				animator_->Play(animation_names[(int)player->get_direction()][(int)player->state_][(int)player->hand_state_]);

		} break;
		}


	}
}

void PlayerRenderComponent::Render(GObject* owner, ID3D11Device* p_d3d_device)
{
	Player* player = dynamic_cast<Player*>(owner);
	float x_direction = player->get_direction() == DIRECTION::LEFT ? -1.f : 1.f;
	if (player) {
		if (!animator_ || animator_->is_finished()) {
			if (sprite_) {
				Vector2 pos = WorldToRenderPos(player->get_pos());
				Vector2 scale = Vector2{ player->get_scale().x * x_direction, player->get_scale().y };
				DrawTexture(p_d3d_device, pos - scale / 2.f, scale, sprite_->get_base_pos(), sprite_->get_scale(), sprite_->get_texture());
			}
		}
		else {
			animator_->Render(p_d3d_device);
		}
	}


	
}

void PlayerRenderComponent::ChangeSprite(GObjectSprite* sprite)
{
	if (sprite_) delete sprite_;
	sprite_ = dynamic_cast<RealObjectSprite*>(sprite);
}

