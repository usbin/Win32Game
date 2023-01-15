#pragma once
#include "global.h"
#include "ITileObjectInfo.h"
class TileObjectSprite;
class NaturalThing : public ITileObjectInfo
{
public:
	~NaturalThing();
private:
	tstring name_;
	TILE_OBJECT_TYPE type_;
	UINT max_level_ = 0;	//캘 수 있는 레벨(0부터 시작, 작물이 되는 레벨, 나무와 돌은 그냥 0)
	TileObjectSprite* sprite_;
	std::map<ITEM_CODE, TileDropItem> drop_items_;

	void Init(TILE_OBJECT_TYPE type, tstring name, TileObjectSprite* sprite);
	virtual void AddDropItem(ITEM_CODE item_code, float drop_rate, UINT amount) override;
public:
	// ITileObjectInfo을(를) 통해 상속됨
	virtual void Update(TileObject* tile_object) const override;
	virtual void Render(TileObject* tile_object, ID3D11Device* p_d3d_device) const override;
	virtual TILE_OBJECT_TYPE get_tile_object_type() const override { return type_; };
	virtual void OnHarvest() const override;

	friend class TileObjectDb;
};

