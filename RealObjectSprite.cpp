#include "RealObjectSprite.h"
#include "GObject.h"
void RealObjectSprite::Render(ID3D11Device* p_d3d_device)
{
	float direction = 1.f;
	switch (get_owner()->get_direction()) {
	case DIRECTION::LEFT: {
		direction = -1.f;
	} break;
	case DIRECTION::RIGHT: {
		direction = 1.f;
	} break;
	}
	const Vector2& pos = WorldToRenderPos(get_owner()->get_pos());
	Vector2 scale{ get_owner()->get_scale().x * direction, get_owner()->get_scale().y };
	Texture* texture = get_texture();
	const Vector2& sprite_base_pos = get_base_pos();
	const Vector2& sprite_scale = get_scale();

	DrawTexture(p_d3d_device, pos - scale / 2.f, scale, sprite_base_pos, sprite_scale, texture);
}