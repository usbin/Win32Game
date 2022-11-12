#pragma once
#include "RealObject.h"
class TileUi;
class Sprite;
class TileCell : public RealObject
{
public:
	TileCell();
	~TileCell();
private:
	bool can_move_;
	bool dragging_;
	Vector2 prev_drag_pos_;
public:
	virtual void Update() override;
	virtual void Render(LPDIRECT3DDEVICE9 p_d3d_device) override;
	void SetTileCell(TileUi* tile_ui);
};
