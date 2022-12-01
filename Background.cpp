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

void Background::Render(ID3D11Device* p_d3d_device)
{
	if (get_sprite()) {
		const Vector2& pos = WorldToRenderPos(get_pos());
		const Vector2& scale = get_scale();

		Sprite* sprite = get_sprite();
		const Vector2& sprite_pos = sprite->get_base_pos();
		const Vector2& sprite_scale = sprite->get_scale();
		
		DrawTexture(p_d3d_device, pos, scale, sprite_pos, sprite_scale, sprite->get_texture());
	}
}
