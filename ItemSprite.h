#pragma once
#include "ISprite.h"
class IItem;
class ItemSprite : public ISprite
{
public:
	ItemSprite();
	ItemSprite(ItemSprite& org);
	~ItemSprite();
private:
	Texture* texture_ = nullptr;
	Vector2 base_pos_ = Vector2::Zero();
	Vector2 scale_ = Vector2::Zero();
	IItem* owner_ = nullptr;
public:
	void QuickSet(Texture* texture, IItem* owner, int row, int column, int max_row, int max_column);
	void QuickSet(Texture* texture, IItem* owner, Vector2 base_pos, Vector2 scale);

	virtual inline void set_texture(Texture* texture) override { texture_ = texture; };
	virtual inline Texture* get_texture() override { return texture_; };
	virtual inline void set_base_pos(Vector2 pos) override { base_pos_ = pos; };
	virtual inline Vector2 get_base_pos() override { return base_pos_; };
	virtual inline void set_scale(Vector2 scale) override { scale_ = scale; };
	virtual inline Vector2 get_scale() override { return scale_; };
	virtual inline void set_owner(IItem* owner) { owner_ = owner; };
	virtual inline IItem* get_owner() { return owner_; };
};

