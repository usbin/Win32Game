#pragma once
#include "global.h"

class InvisibleWall;
class Tile;
class IFileSaver
{
public:

	virtual void SaveWall(FILE* p_file, InvisibleWall* wall) = 0;
	virtual InvisibleWall* LoadWall(FILE* p_file) = 0;
	virtual void SaveTile(FILE* p_file, Tile* tile) = 0;
	virtual Tile* LoadTile(FILE* p_file) = 0;
	virtual void SaveTilemapToFile(FILE* p_file) = 0;
	virtual void LoadTilemapFromFile(FILE* p_file) = 0;
	virtual void SaveWallToFile(FILE* p_file) = 0;
	virtual void LoadWallFromFile(FILE* p_file) = 0;
	virtual void SaveMapToFile(FILE* p_file)=0;
	virtual void LoadMapFromFile(FILE* p_file)=0;
};

