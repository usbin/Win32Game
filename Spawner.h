#pragma once
#include "global.h"
class Core;
/// <summary>
/// �ڿ���(��, ����, ����), ���� �� ������
/// </summary>
class Spawner
{
	SINGLETON(Spawner);

public:
	void RandomSpawn(TILE_OBJECT_TYPE type, Vector2 left_top, Vector2 bottom_right, UINT amount);


	friend class Core;
};

