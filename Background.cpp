#include "Background.h"
#include "Sprite.h"
#include "Texture.h"
Background::Background()
{
}

Background::~Background()
{
}

void Background::Update()
{
}

void Background::Render(LPDIRECT3DDEVICE9 p_d3d_device)
{
	/*if (get_sprite()) {
		const Vector2& pos = WorldToRenderPos(get_pos());
		const Vector2& scale = get_scale();

		Sprite* sprite = get_sprite();
		const Vector2& sprite_pos = sprite->get_base_pos();
		const Vector2& sprite_scale = sprite->get_scale();
		
		TransparentBlt(hdc
			, static_cast<int>(pos.x)
			, static_cast<int>(pos.y)
			, static_cast<int>(scale.x)
			, static_cast<int>(scale.y)
			, sprite->get_texture()->get_hdc()
			, static_cast<int>(sprite_pos.x)
			, static_cast<int>(sprite_pos.y)
			, static_cast<int>(sprite_scale.x)
			, static_cast<int>(sprite_scale.y)
			, RGB(255, 0, 255));
	}*/
}
