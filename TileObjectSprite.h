#pragma once
#include "global.h"
#include "ISprite.h"
class Texture;
class TileObject;
class TileObjectSprite : public ISprite
{
private:
	Texture* texture_ = nullptr;
	Vector2 base_pos_ = Vector2::Zero();
	Vector2 scale_ = Vector2::Zero();
	TileObject* owner_ = nullptr;

public:
	void QuickSet(Texture* texture, TileObject* owner, int row, int column, int max_row, int max_column);
	void QuickSet(Texture* texture, TileObject* owner, Vector2 base_pos, Vector2 scale);
	virtual void Render(ID3D11Device* p_d3d_device);
	// ISprite을(를) 통해 상속됨
	virtual void set_texture(Texture* texture) override { texture_ = texture; };
	virtual Texture* get_texture() override { return texture_; };
	virtual void set_base_pos(Vector2 pos) override { base_pos_ = pos; };
	virtual Vector2 get_base_pos() override { return base_pos_; };
	virtual void set_scale(Vector2 scale) override { scale_ = scale; };
	virtual Vector2 get_scale() override { return scale_; };
};

