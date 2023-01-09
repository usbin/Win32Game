#pragma once
#include "global.h"
#include "IItem.h"
#include "IUsable.h"
class FieldTileObject;
class Crop : public IUsable, public IItem
{
private:
	Crop() {};
	~Crop();

	int item_code_ = 0;
	tstring name_;
	ItemSprite* sprite_ = nullptr;
	UINT max_level_ = 0;
	std::vector<ItemSprite*> sprites_;
	Vector2 scale_ = Vector2{};

public:
	IItem* Init(int item_code, tstring name, UINT max_level);
	virtual void OnHold(RealObject* owner) const override;
	virtual void Use(RealObject* obj) const override;
	inline void set_level_sprite(UINT level, ItemSprite* sprite) { if(sprites_.size() > level) sprites_[level] = sprite;};
	inline ItemSprite* get_level_sprite(UINT level) const { return max_level_>=level ? sprites_[level] : nullptr; };
	virtual int get_item_code() const override;
	virtual ItemSprite* get_sprite() const override { return sprite_; };


	friend class ItemDb;

	// IItem을(를) 통해 상속됨
	virtual void UpdateOnHolder(IItemHolder* holder) const override;
	virtual void RenderOnHolder(IItemHolder* holder, ID3D11Device* p_d3d_device) const override;

	void UpdateOnField(FieldTileObject* field_tile_object) const; 
	void RenderOnField(FieldTileObject* field_tile_object, ID3D11Device* p_d3d_device) const;



	// IItem을(를) 통해 상속됨
	virtual void set_scale(Vector2 scale) override { scale_ = scale; };
	virtual Vector2 get_scale() const override { return scale_; };
};

