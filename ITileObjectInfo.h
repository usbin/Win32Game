#pragma once
#include "global.h"
#include "TileObjectDb.h"
class TileObject;
class TileObjectSprite;
/// <summary>
/// TileObject에 셋팅할 정보.
/// 밭, 돌, 나무, 잡초
/// </summary>
class ITileObjectInfo
{
private:

	virtual void AddDropItem(ITEM_CODE item_code, float drop_rate, UINT amount) = 0;
public:
	virtual ~ITileObjectInfo() = 0 {};
	virtual void Update(TileObject* tile_object)  const= 0;
	virtual void Render(TileObject* tile_object, ID3D11Device* p_d3d_device) const=0;
	virtual TILE_OBJECT_TYPE get_tile_object_type()  const = 0;
	virtual void OnHarvest() const = 0;
	
	friend class FileObjectDb;
};

struct TileDropItem {
	ITEM_CODE item_code;
	float drop_rate;
	UINT amount;
};