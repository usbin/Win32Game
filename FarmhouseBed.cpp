#include "FarmhouseBed.h"
#include "Collider.h"
#include "Player.h"
#include "DayFinishedUi.h"
#include "Core.h"
#include "AskSleepUi.h"
void FarmhouseBed::Init()
{
	CreateCollider();
}

void FarmhouseBed::CreateCollider()
{
	Collider* collider = DEBUG_NEW Collider();
	collider->set_owner(this);
	collider->set_scale(get_scale());
	collider->set_is_physical_collider(false);
	set_collider(collider);
}

void FarmhouseBed::Update()
{
}

void FarmhouseBed::OnCollisionEnter(Collider* collider)
{
	if (collider->get_owner()) {
		Player* player = dynamic_cast<Player*>(collider->get_owner());
		if (player) {
			//닿은 게 player면 정산 화면으로 넘어감.
			AskSleepUi* ui = DEBUG_NEW AskSleepUi(true);
			ui->set_scale(Vector2{ 220, 100 });
			ui->set_pos((Core::GetInstance()->get_resolution() - ui->get_scale()) / 2.f);
			ui->set_group_type(GROUP_TYPE::UI);
			ui->Init();
			CreateGObject(ui, GROUP_TYPE::UI);
		}
	}
}
