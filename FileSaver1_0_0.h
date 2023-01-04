#pragma once
#include "global.h"
#include "IFileSaver.h"
class Background;
class InvisibleWall;
class Tile;
class GObject;
class Res;
class GObjectSprite;
class Texture;

class FileSaver1_0_0 : public IFileSaver
{
public:
	SINGLETON(FileSaver1_0_0);
public:
	void SaveGObject(FILE* p_file, GObject* gobject);
	void LoadGObject(FILE* p_file, GObject*& gobject);
	void SaveGObjectSprite(FILE* p_file, GObjectSprite* sprite);
	void LoadGObjectSprite(FILE* p_file, GObjectSprite*& sprite, GObject* owner);
	void SaveTexture(FILE* p_file, Texture* texture);
	void LoadTexture(FILE* p_file, Texture*& texture);

	void SaveBackground(FILE* p_file, Background* background);
	Background* LoadBackground(FILE* p_file);
	void SaveWall(FILE* p_file, InvisibleWall* wall);
	InvisibleWall* LoadWall(FILE* p_file);
	void SaveTile(FILE* p_file, Tile* tile);
	Tile* LoadTile(FILE* p_file);

	// IFileSaver을(를) 통해 상속됨
	virtual void SaveTilemapToFile(FILE* p_file) override;
	virtual void LoadTilemapFromFile(FILE* p_file) override;
	virtual void SaveWallToFile(FILE* p_file) override;
	virtual void LoadWallFromFile(FILE* p_file) override;
	virtual void SaveMapToFile(FILE* p_file) override;
	virtual void LoadMapFromFile(FILE* p_file) override;
};

