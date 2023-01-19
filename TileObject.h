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
	UINT updated_day_ = 0;	//몇일차로 업뎃된 상태인가
public:
	virtual void Init(TILE_OBJECT_TYPE tile_object_type_);
	void CreateRenderCmp();
	void SetLevel(UINT level);
	// RealObject을(를) 통해 상속
	virtual void Update() override;
	virtual void Render(ID3D11Device* p_d3d_device) override;
	virtual UINT get_level() { return level_; };
	UINT get_updated_day() { return updated_day_; };
	void UpdateDay(UINT day) { updated_day_ = day; };
	
	const ITileObjectInfo* get_tile_object_info();
	TILE_OBJECT_TYPE get_tile_object_type() { return tile_object_type_; };
};


