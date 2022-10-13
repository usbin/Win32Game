#include "TileCell.h"
#include "TileUi.h"
#include "Sprite.h"
#include "Texture.h"

TileCell::TileCell()
	: can_move_(true)
	, dragging_(false)
{
}

TileCell::~TileCell()
{
}

void TileCell::Update()
{
}

void TileCell::Render(HDC hdc)
{
	Sprite* sprite = get_sprite();
	Vector2 pos = WorldToRenderPos(get_pos());
	Vector2 scale = get_scale();
	if (sprite == nullptr) {
		//스프라이트가 없으면 마젠타 네모 그리기
		Rectangle(hdc, pos.x, pos.y, pos.x + scale.x, pos.y + scale.y);
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

void TileCell::SetTileCell(TileUi* tile_ui)
{
	Sprite* new_sp = new Sprite(*tile_ui->get_sprite());
	ChangeSprite(new_sp);

}
