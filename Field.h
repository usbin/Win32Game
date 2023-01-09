#pragma once
#include "global.h"
#include "ITileObjectInfo.h"
class Crop;
class TileObjectSprite;


const int FIELD_CONNECTED_UP = 0b1000;
const int FIELD_CONNECTED_RIGHT = 0b0100;
const int FIELD_CONNECTED_DOWN = 0b0010;
const int FIELD_CONNECTED_LEFT = 0b0001;
class Field : public ITileObjectInfo
{
public:
	~Field();
private:
	tstring name_;
	TILE_OBJECT_TYPE type_;
	TileObjectSprite* sprites_[2][16];	//[¡•¿Ω ø©∫Œ][æ’øÏπÿ¡¬ ø¨∞· ø©∫Œ]

public:
	// ITileObjectInfo¿ª(∏¶) ≈Î«ÿ ªÛº”µ 
	void Init(TILE_OBJECT_TYPE type, tstring name);
	void SetSprite(bool is_watered, int field_connected, TileObjectSprite* sprite);
	virtual void Update(TileObject* tile_object) const override;
	virtual void Render(TileObject* tile_object, ID3D11Device* p_d3d_device) const override;
	virtual TILE_OBJECT_TYPE get_tile_object_type() const override { return type_; };




};

