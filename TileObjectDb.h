#pragma once
#include "global.h"
class ITileObjectInfo;
class TileObjectDb
{
	SINGLETON(TileObjectDb);

private:
	
	ITileObjectInfo* tile_object_infos[(int)TILE_OBJECT_TYPE::END] = { nullptr };
public:
	void Init();
	ITileObjectInfo* get_tile_object_info(TILE_OBJECT_TYPE type) { return tile_object_infos[(int)type]; };

};

