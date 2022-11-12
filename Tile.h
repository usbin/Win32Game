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
	virtual void Render(LPDIRECT3DDEVICE9 p_d3d_device) override;
	void SetTile(TileUi* tile_ui);
	void ResetTile();
	virtual void SaveToFile(FILE* p_file) override;
};

