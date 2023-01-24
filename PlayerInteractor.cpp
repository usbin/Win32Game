#include "PlayerInteractor.h"
#include "Player.h"
#include "IItemHolder.h"
#include "SceneManager.h"
void PlayerInteractor::Update()
{
	if (get_owner()) {
		Player* player = dynamic_cast<Player*>(get_owner());
		if (player->get_item_holder()) {
			Vector2 target_pos = player->get_item_holder()->get_target_pos();
			Vector2 tile_base_pos;
			SceneManager::GetInstance()->get_current_scene()->GetTilePos(target_pos, tile_base_pos);
			set_pos(tile_base_pos);
			get_collider()->set_scale(Vector2{ TILE_WIDTH, TILE_HEIGHT });
		}
		
		
	}
}
