#include "FarmhouseDoor_Exit.h"
#include "Collider.h"
#include "Player.h"
void FarmhouseDoor_Exit::Init()
{
	CreateCollider();
}
void FarmhouseDoor_Exit::CreateCollider()
{
	Collider* collider = DEBUG_NEW Collider();
	collider->set_owner(this);
	collider->set_scale(get_scale());
	collider->set_is_physical_collider(false);
	set_collider(collider);
}
void FarmhouseDoor_Exit::Update()
{
}

void FarmhouseDoor_Exit::OnCollisionEnter(Collider* collider)
{
	if (collider->get_owner()) {
		Player* player = dynamic_cast<Player*>(collider->get_owner());
		if (player) {
			//¥Í¿∫ ∞‘ player∏È æ¿ ¿Ãµø
			ChangeScene(SCENE_TYPE::SCENE_FARM);
		}
	}
}
