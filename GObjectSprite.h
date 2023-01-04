#pragma once
#include "global.h"
#include "ISprite.h"
class GObjectSprite : public ISprite
{
public:
	GObjectSprite();
	GObjectSprite(const GObjectSprite& org);
	~GObjectSprite();

private:

	Texture* texture_ = nullptr;
	Vector2 base_pos_ = Vector2::Zero();
	Vector2 scale_ = Vector2::Zero();
	GObject* owner_ = nullptr;

public:
	void Render(ID3D11Device* p_d3d_device) override {};
	void QuickSet(Texture* texture, GObject* owner, int row, int column, int max_row, int max_column);
	void QuickSet(Texture* texture, GObject* owner, Vector2 base_pos, Vector2 scale);
	inline void set_texture(Texture* texture) { texture_ = texture; };
	inline Texture* get_texture() { return texture_; };
	inline void set_base_pos(Vector2 pos) { base_pos_ = pos; };
	inline Vector2 get_base_pos() { return base_pos_; };
	inline void set_scale(Vector2 scale) { scale_ = scale; };
	inline Vector2 get_scale() { return scale_; };
	inline void set_owner(GObject* owner) { owner_ = owner; };
	inline GObject* get_owner() { return owner_; };
};

