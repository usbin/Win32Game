#pragma once
#include "global.h"
/// <summary>
/// 자연물(돌, 나무, 잡초), 몬스터 등 생성기
/// </summary>
class Spawner
{
	SINGLETON(Spawner);

public:
	void RandomSpawn(TILE_OBJECT_TYPE type, Vector2 left_top, Vector2 bottom_right, UINT amount);
};

