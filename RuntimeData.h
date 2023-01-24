#pragma once
#include "global.h"
#include "Player.h"

/// <summary>
/// ���α׷� ���� ���� �����͸� �����ϴ� ��.
/// (�÷��̾� ����, �κ��丮 ��)
/// �� �̵��� ����
/// 1. �̱��� �κ��丮Ui�� �����Ѵ�.
/// 2. �̱��� �ܼ�Ui�� �����Ѵ�.
/// 3. �̵��� �ʿ� �÷��̾ �����ϴ��� üũ, �ִٸ� enable�� true�� ����� ���� ���� �÷��̾�� �����͸� ����ȭ�Ѵ�. ���ٸ� ���� �����ϰ� �����͸� ����ȭ�Ѵ�.
///  - ����ȭ�� ������: ����...
/// </summary>
class RuntimeData
{
	SINGLETON(RuntimeData);
private:
	Player* player_ = nullptr;

public:
	void SavePlayerData(Player* player);	//���ο� �÷��̾� �����͸� ����
	void LoadPlayerData(Player* player);	//���ο� ����� �÷��̾� �����͸� �������� �÷��̾�� �ε�

	void OnDestroy();//�ý��� ������ ��
};

