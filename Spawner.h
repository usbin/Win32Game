#pragma once
#include "global.h"
class Core;
/// <summary>
/// �ڿ���(��, ����, ����), ���� �� ������
/// </summary>
class Spawner
{
	SINGLETON(Spawner);
	std::vector<Vector2> pos_log_;
	bool lock_ = false;
public:
	void RandomSpawn(TILE_OBJECT_TYPE type, Vector2 left_top, Vector2 bottom_right, UINT amount);
	void Lock();	//�ߺ� ���� ����.
	void Unlock();
	void SetSeed(int seed);

	friend class Core;
};

