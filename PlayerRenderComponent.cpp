#include "PlayerRenderComponent.h"
#include "Player.h"
#include "RealObjectSprite.h"
#include "RealObjectAnimator.h"
#include "ResManager.h"
#include "RealObjectSprite.h"

PlayerRenderComponent::PlayerRenderComponent(GObject* owner)
	:RealObjectRenderComponent(owner)
{
	Texture* texture = ResManager::GetInstance()->LoadTexture(_T("player"), _T("texture\\StardewValley_Player.png"));
	Sprite* sprite_front = new RealObjectSprite();
	Sprite* sprite_back = new RealObjectSprite();
	Sprite* sprite_right = new RealObjectSprite();
	Sprite* sprite_left = new RealObjectSprite();
	Sprite* sprite_hold_front = new RealObjectSprite();
	Sprite* sprite_hold_back = new RealObjectSprite();
	Sprite* sprite_hold_right = new RealObjectSprite();
	Sprite* sprite_hold_left = new RealObjectSprite();
	sprite_front->QuickSet(texture, owner, Vector2{ 0, 0 }, Vector2{ 16, 32 });
	sprite_back->QuickSet(texture, owner, Vector2{ 0, 64 }, Vector2{ 16, 32 });
	sprite_right->QuickSet(texture, owner, Vector2{ 0, 32 }, Vector2{ 16, 32 });
	sprite_left->QuickSet(texture, owner, Vector2{ 0, 32 }, Vector2{ 16, 32 });
	sprite_hold_front->QuickSet(texture, owner, Vector2{ 112, 0 }, Vector2{ 16, 32 });
	sprite_hold_back->QuickSet(texture, owner, Vector2{ 112, 64 }, Vector2{ 16, 32 });
	sprite_hold_right->QuickSet(texture, owner, Vector2{ 112, 32 }, Vector2{ 16, 32 });
	sprite_hold_left->QuickSet(texture, owner, Vector2{ 112, 32 }, Vector2{ 16, 32 });
	sprites[(int)DIRECTION::UP][(int)PLAYER_STATE::IDLE] = sprite_back;
	sprites[(int)DIRECTION::RIGHT][(int)PLAYER_STATE::IDLE] = sprite_right;
	sprites[(int)DIRECTION::LEFT][(int)PLAYER_STATE::IDLE] = sprite_left;
	sprites[(int)DIRECTION::DOWN][(int)PLAYER_STATE::IDLE] = sprite_front;
	sprites[(int)DIRECTION::UP][(int)PLAYER_STATE::HOLD] = sprite_hold_back;
	sprites[(int)DIRECTION::RIGHT][(int)PLAYER_STATE::HOLD] = sprite_hold_right;
	sprites[(int)DIRECTION::LEFT][(int)PLAYER_STATE::HOLD] = sprite_hold_left;
	sprites[(int)DIRECTION::DOWN][(int)PLAYER_STATE::HOLD] = sprite_hold_front;

}

PlayerRenderComponent::~PlayerRenderComponent()
{
	for (int i = 0; i < (int)DIRECTION::END; i++) {
		for (int j = 0; j < (int)PLAYER_STATE::END; j++) {
			if (sprites[i][j]) {
				delete sprites[i][j];
				sprites[i][j] = nullptr;
			}
		}
	}
}

void PlayerRenderComponent::Update(GObject* owner)
{




}

void PlayerRenderComponent::Render(GObject* owner, ID3D11Device* p_d3d_device)
{
	
	Player* player = dynamic_cast<Player*>(owner);
	Vector2 v = player->get_velocity();

	float x_direction = player->get_direction() != DIRECTION::LEFT ? 1.f : -1.f;
	if (player) {
		switch (player->state_) {
		case PLAYER_STATE::IDLE: {
			player->get_animator()->Stop();
			Vector2 pos = WorldToRenderPos(player->get_pos());
			Vector2 scale = Vector2{ player->get_scale().x * x_direction, player->get_scale().y };
			Sprite* sprite = sprites[(int)player->get_direction()][(int)player->state_];
			DrawTexture(p_d3d_device, pos - scale / 2.f, scale, sprite->get_base_pos(), sprite->get_scale(), sprite->get_texture());
		} break;
		case PLAYER_STATE::WALK: {
			//ChangeSprite(new RealObjectSprite(*dynamic_cast<RealObjectSprite*>(sprites[(int)player->get_direction()][(int)player->state_])));
			switch (player->get_direction())
			{
			case DIRECTION::UP:
				if (!player->get_animator()->is_current_playing(_T("Walk_Back")))
					player->get_animator()->Play(_T("Walk_Back"));
				break;
			case DIRECTION::DOWN:
				if (!player->get_animator()->is_current_playing(_T("Walk_Front")))
					player->get_animator()->Play(_T("Walk_Front"));
				break;
			case DIRECTION::LEFT:
				if (!player->get_animator()->is_current_playing(_T("Walk_Left")))
					player->get_animator()->Play(_T("Walk_Left"));
				break;
			case DIRECTION::RIGHT:
				if (!player->get_animator()->is_current_playing(_T("Walk_Right")))
					player->get_animator()->Play(_T("Walk_Right"));
				break;
			}
				
		} break;
		}


	}
}

void PlayerRenderComponent::SaveToFile(FILE* p_file)
{
}

void PlayerRenderComponent::LoadFromFile(FILE* p_file)
{
}
