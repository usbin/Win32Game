#pragma once
#include "global.h"
class Texture;
class GObject;
/// <summary>
/// GObject가 포인터로 갖고 있는 이미지 정보.
/// </summary>
class Sprite
{
public:
	Sprite();
	Sprite(const Sprite& org);
	~Sprite();

private:
	Texture* texture_;
	Vector2 base_pos_;
	Vector2 scale_;
	GObject* owner_;


public:
	void QuickSet(Texture* texture, GObject* owner, int row, int column, int max_row, int max_column);
	void QuickSet(Texture* texture, GObject* owner, Vector2 base_pos, Vector2 scale);
	virtual void Render(ID3D11Device* p_d3d_device);

	inline void set_texture(Texture* texture) { texture_ = texture; };
	inline Texture* get_texture() { return texture_; };
	inline void set_base_pos(Vector2 pos) { base_pos_ = pos; };
	inline Vector2 get_base_pos() { return base_pos_; };
	inline void set_scale(Vector2 scale) { scale_ = scale; };
	inline Vector2 get_scale() { return scale_; };
	inline void set_owner(GObject* owner) { owner_ = owner; };
	inline GObject* get_owner() { return owner_; };




};

