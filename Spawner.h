#pragma once
#include "global.h"
class Core;
/// <summary>
/// 자연물(돌, 나무, 잡초), 몬스터 등 생성기
/// </summary>
class Spawner
{
	SINGLETON(Spawner);
	std::vector<Vector2> pos_log_;
	bool lock_ = false;
public:
	void RandomSpawn(TILE_OBJECT_TYPE type, Vector2 left_top, Vector2 bottom_right, UINT amount);
	void Lock();	//중복 없는 구간.
	void Unlock();
	void SetSeed(int seed);

	friend class Core;
};

