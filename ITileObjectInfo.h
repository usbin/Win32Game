#pragma once
#include "global.h"
class TileObject;
class TileObjectSprite;
/// <summary>
/// TileObject�� ������ ����.
/// ��, ��, ����, ����
/// </summary>
class ITileObjectInfo
{
public:
	virtual ~ITileObjectInfo() = 0 {};
	virtual void Update(TileObject* tile_object)  const= 0;
	virtual void Render(TileObject* tile_object, ID3D11Device* p_d3d_device) const=0;
	virtual TILE_OBJECT_TYPE get_tile_object_type()  const = 0;
	
};

