#include "RuntimeData.h"
#include "Interactor.h"

RuntimeData::RuntimeData() {};
RuntimeData::~RuntimeData() {
};

void RuntimeData::SavePlayerData(Player* player)
{
	if (!player_) {
		player_ = DEBUG_NEW Player();
	}
	player->MoveTo(player_);

	//인터렉터는 씬에 종속적이므로 저장하지 않고 삭제.
	DeleteGObject(player_->get_interactor(), GROUP_TYPE::INTERACTOR);
	player_->set_interactor(nullptr);
}

void RuntimeData::LoadPlayerData(Player* player)
{
	if (player_) {
		player_->MoveTo(player);
	}
}

void RuntimeData::OnDestroy()
{
	if (player_) DeleteGObject(player_, GROUP_TYPE::PLAYER);
	//소멸자는 호출 시점을 모르기 때문에 명시적으로 호출해줌.
}
