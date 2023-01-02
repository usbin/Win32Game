#pragma once
#include "global.h"
class IFileSaver
{
public:

	virtual void SaveTilemapToFile(FILE* p_file) = 0;
	virtual void LoadTilemapFromFile(FILE* p_file) = 0;
	virtual void SaveWallToFile(FILE* p_file) = 0;
	virtual void LoadWallFromFile(FILE* p_file) = 0;
	virtual void SaveMapToFile(FILE* p_file)=0;
	virtual void LoadMapFromFile(FILE* p_file)=0;
};

