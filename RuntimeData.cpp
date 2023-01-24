#include "RuntimeData.h"
#include "Interactor.h"

RuntimeData::RuntimeData() {};
RuntimeData::~RuntimeData() {
};

void RuntimeData::SavePlayerData(Player* player)
{
	if (!player_) {
		player_ = DEBUG_NEW Player();
		//���ͷ��ʹ� ���� �������̹Ƿ� ����� �������� ���� �׳� ����.
		DeleteGObject(player_->get_interactor(), GROUP_TYPE::INTERACTOR);
		player_->set_interactor(nullptr);
	}
	player->MoveTo(player_);

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
	//�Ҹ��ڴ� ȣ�� ������ �𸣱� ������ ��������� ȣ������.
}
