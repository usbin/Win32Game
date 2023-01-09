#include "Tile.h"
#include "Texture.h"
#include "RealObjectSprite.h"
#include "TileUi.h"

Tile::Tile()
{
	render_cmp_ = DEBUG_NEW RealObjectRenderComponent(this);
}

Tile::~Tile()
{
}

void Tile::Update()
{

}

void Tile::Render(ID3D11Device* p_d3d_device)
{

	ISprite* sprite = get_sprite();
	Vector2 pos = WorldToRenderPos(get_pos());
	Vector2 scale = get_scale();
	if (sprite == nullptr) {
		//스프라이트가 없으면 마젠타 네모 그리기
		DrawRectangle(p_d3d_device, pos - scale / 2.f, scale, ARGB(0xFFFF00FF));
		
	}
	else {

		DrawTexture(p_d3d_device, pos - scale / 2.f, scale, sprite->get_base_pos(), sprite->get_scale(), sprite->get_texture());
	}
}

void Tile::SetTile(TileUi* tile_ui)
{
	if (render_cmp_) {
		RealObjectSprite* sprite = DEBUG_NEW RealObjectSprite();
		sprite->QuickSet(tile_ui->get_sprite()->get_texture(), this, tile_ui->get_sprite()->get_base_pos(), tile_ui->get_sprite()->get_scale());
		render_cmp_->ChangeSprite(sprite);
	}
}

void Tile::ResetTile()
{
	if (render_cmp_) {
		render_cmp_->ChangeSprite(nullptr);
	}
	
}