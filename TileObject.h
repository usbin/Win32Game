#pragma once
#include "global.h"
#include "RealObject.h"
#include "Field.h"
class ITileObjectInfo;
class TileObject : public RealObject
{
public:
	~TileObject();
private:
	TILE_OBJECT_TYPE tile_object_type_;
	const ITileObjectInfo* tile_object_info_ = nullptr;
	UINT level_ = 0;
public:
	virtual void Init(TILE_OBJECT_TYPE tile_object_type_);
	void CreateRenderCmp();
	// RealObject을(를) 통해 상속
	virtual void Update() override;
	virtual void Render(ID3D11Device* p_d3d_device) override;
	virtual UINT get_level() { return level_; };
	
	const ITileObjectInfo* get_tile_object_info();
	TILE_OBJECT_TYPE get_tile_object_type() { return tile_object_type_; };
};


