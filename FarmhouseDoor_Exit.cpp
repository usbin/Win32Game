#include "FarmhouseDoor_Exit.h"
#include "Collider.h"
#include "Player.h"
#include "FmodSound.h"
#include "ResManager.h"
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
			//´êÀº °Ô player¸é ¾À ÀÌµ¿
			ChangeScene(SCENE_TYPE::SCENE_FARM);
			Sound* sound = ResManager::GetInstance()->LoadSound(_T("DoorOpen_Effect"), _T("sound\\DoorOpen_Effect.wav"));
			FmodSound::GetInstance()->Play(FmodSound::GetInstance()->GetChannel(), sound, false);
		}
	}
}
