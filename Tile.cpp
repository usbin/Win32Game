#include "Tile.h"
#include "Texture.h"
#include "Sprite.h"
#include "TileUi.h"

Tile::Tile()
{
}

Tile::~Tile()
{
}

void Tile::Update()
{
}

void Tile::Render(HDC hdc)
{
	Sprite* sprite = get_sprite();
	Vector2 pos = WorldToRenderPos(get_pos());
	Vector2 scale = get_scale();
	if (sprite == nullptr) {
		//��������Ʈ�� ������ ����Ÿ �׸� �׸���
		Rectangle(hdc
			, static_cast<int>(pos.x)
			, static_cast<int>(pos.y)
			, static_cast<int>(pos.x + scale.x)
			, static_cast<int>(pos.y + scale.y));
	}
	else {
		Texture* texture = sprite->get_texture();
		const Vector2& sprite_base_pos = sprite->get_base_pos();
		const Vector2& sprite_scale = sprite->get_scale();
		TransparentBlt(hdc
			, static_cast<int>(pos.x)
			, static_cast<int>(pos.y)
			, static_cast<int>(scale.x)
			, static_cast<int>(scale.y)
			, texture->get_hdc()
			, static_cast<int>(sprite_base_pos.x)
			, static_cast<int>(sprite_base_pos.y)
			, static_cast<int>(sprite_scale.x)
			, static_cast<int>(sprite_scale.y)
			, RGB(255, 0, 255));
	}
}

void Tile::SetTile(TileUi* tile_ui)
{
	ChangeSprite(new Sprite(*tile_ui->get_sprite()));
}

void Tile::ResetTile()
{
	ChangeSprite(nullptr);
}
