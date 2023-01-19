#pragma once
#include "global.h"
#include "IItem.h"
#include "IUsable.h"
class FieldTileObject;
class Seed : public IItem, public IUsable
{
private:
	Seed() {};
	~Seed();

	int item_code_ = 0;
	tstring name_;
	ItemSprite* sprite_ = nullptr;
	ItemSprite* profile_sprite_ = nullptr;
	Vector2 scale_{};

	int crop_code_ = 0; //밭에 심으면 되는 작물
	UINT max_level_ = 0;
	std::vector<ItemSprite*> sprites_;
	const UINT MAX_STACK = 99;
	UINT price_ = 0;
	const Vector2 item_hold_offset{ 0, -40 };
	const Vector2 item_hold_scale{ 48, 48 };


	virtual IItem* Init(int item_code, int crop_code, UINT max_level, tstring name, UINT price);
	virtual void set_scale(Vector2 scale) override { scale_ = scale; };
	inline void set_level_sprite(UINT level, ItemSprite* sprite) { if (sprites_.size() > level) sprites_[level] = sprite; };
	virtual ItemSprite* get_profile_sprite() const override { return profile_sprite_; };

public:
	virtual void UpdateOnHolder(IItemHolder* holder) const override;
	virtual void RenderOnHolder(IItemHolder* holder, ID3D11Device* p_d3d_device) const override;
	void UpdateOnField(FieldTileObject* field_tile_object) const;
	void RenderOnField(FieldTileObject* field_tile_object, ID3D11Device* p_d3d_device) const;


	virtual bool Use(RealObject* obj) const override;
	virtual void OnHold(RealObject* owner) const override;


	virtual int get_item_code() const override;
	virtual ItemSprite* get_sprite() const override { return sprite_; };
	inline ItemSprite* get_level_sprite(UINT level) const { return max_level_ >= level ? sprites_[level] : nullptr; };
	virtual Vector2 get_scale() const override { return scale_; };
	virtual UINT get_max_stack() const override { return MAX_STACK; };
	virtual UINT get_price() const override { return price_; };
	UINT get_max_level() const { return max_level_; };
	friend class ItemDb;




};

