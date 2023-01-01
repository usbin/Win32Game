#include "Tile.h"
#include "Texture.h"
#include "RealObjectSprite.h"
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

void Tile::Render(ID3D11Device* p_d3d_device)
{

	Sprite* sprite = get_sprite();
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
		render_cmp_->ChangeSprite(new RealObjectSprite(*dynamic_cast<RealObjectSprite*>(tile_ui->get_sprite())));
	}
}

void Tile::ResetTile()
{
	if (render_cmp_) {
		render_cmp_->ChangeSprite(nullptr);
	}
	
}

void Tile::SaveToFile(FILE* p_file)
{
	RealObject::SaveToFile(p_file);
}
