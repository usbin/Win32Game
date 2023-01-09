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
	UINT max_level_ = 0;	//Ķ �� �ִ� ����(0���� ����, �۹��� �Ǵ� ����, ������ ���� �׳� 0)
	TileObjectSprite* sprite_;
public:
	void Init(TILE_OBJECT_TYPE type, tstring name, TileObjectSprite* sprite);
	// ITileObjectInfo��(��) ���� ��ӵ�
	virtual void Update(TileObject* tile_object) const override;
	virtual void Render(TileObject* tile_object, ID3D11Device* p_d3d_device) const override;
	virtual TILE_OBJECT_TYPE get_tile_object_type() const override { return type_; };


};

