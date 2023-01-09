#pragma once
#include "global.h"
#include "TileObject.h"
class Crop;
class FieldTileObject : public TileObject
{
public:
	FieldTileObject();
	~FieldTileObject();
private:
	bool watered_ = false;
	int field_connected_ = 0;
	int water_connected_ = 0;
	const Crop* crop_ = nullptr;
	UINT level_ = 0;
public:
	void Init(TILE_OBJECT_TYPE tile_object_type_) override;
	void SetCrop(const Crop* crop, UINT level);
	void Water();
	virtual void Update() override;
	virtual void Render(ID3D11Device* p_d3d_device) override;
	bool is_watered() { return watered_; };
	int get_field_connected() { return field_connected_; };
	int get_water_connected() { return water_connected_; };
	void SetConnected(int connected_field);
	void SetDisconnected(int connected_field);
	void SetWaterConnected(int connected_water);
};

