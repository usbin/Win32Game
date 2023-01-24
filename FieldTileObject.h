#pragma once
#include "global.h"
#include "TileObject.h"
class Seed;
class FieldTileObject : public TileObject
{
public:
	FieldTileObject();
	~FieldTileObject();
private:
	bool watered_ = false;
	int field_connected_ = 0;
	int water_connected_ = 0;
	const Seed* seed_ = nullptr;
	UINT seed_day_ = 0;	//¾¾¾ÑÀÌ ½É¾îÁø ³¯.
public:
	void Init(TILE_OBJECT_TYPE tile_object_type_) override;
	void CreateInteractor() override;
	void SetSeed(const Seed* seed);
	void Water();
	void Harvest();
	void CheckConnected();
	virtual void Update() override;
	virtual void Render(ID3D11Device* p_d3d_device) override; 
	bool is_watered() { return watered_; };
	const Seed* get_seed() { return seed_; };
	int get_field_connected() { return field_connected_; };
	int get_water_connected() { return water_connected_; };
	void SetConnected(int connected_field);
	void SetDisconnected(int connected_field);
	void SetWaterConnected(int connected_water);

	virtual void OnInteract(const GObject* req_obj);
};

