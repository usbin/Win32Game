#pragma once
#include "RealObject.h"
class TileUi;

class Tile : public RealObject
{
public:
	Tile();
	~Tile();
private:

public:
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	void SetTile(TileUi* tile_ui);
	void ResetTile();
	virtual void SaveToFile(FILE* p_file) override;
};

