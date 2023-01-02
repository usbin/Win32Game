#pragma once
#include "global.h"
#include "IFileSaver.h"
class Background;
class InvisibleWall;
class Tile;
class GObject;
class Res;
class Sprite;
class Texture;

class FileSaver1_0_0 : public IFileSaver
{
public:
	SINGLETON(FileSaver1_0_0);
public:
	void SaveGObject(FILE* p_file, GObject* gobject);
	void LoadGObject(FILE* p_file, GObject** gobject);
	void SaveSprite(FILE* p_file, Sprite* sprite);
	void LoadSprite(FILE* p_file, Sprite** sprite, GObject* owner);
	void SaveTexture(FILE* p_file, Texture* texture);
	void LoadTexture(FILE* p_file, Texture** texture);

	void SaveBackground(FILE* p_file, Background* background);
	void LoadBackground(FILE* p_file, Background** background);
	void SaveWall(FILE* p_file, InvisibleWall* wall);
	void LoadWall(FILE* p_file, InvisibleWall** wall);
	void SaveTile(FILE* p_file, Tile* tile);
	void LoadTile(FILE* p_file, Tile** tile);

	// IFileSaver을(를) 통해 상속됨
	virtual void SaveTilemapToFile(FILE* p_file) override;
	virtual void LoadTilemapFromFile(FILE* p_file) override;
	virtual void SaveWallToFile(FILE* p_file) override;
	virtual void LoadWallFromFile(FILE* p_file) override;
	virtual void SaveMapToFile(FILE* p_file) override;
	virtual void LoadMapFromFile(FILE* p_file) override;
};

