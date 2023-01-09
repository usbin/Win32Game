#include "TileObjectSprite.h"
#include "TileObject.h"
#include "Texture.h"
void TileObjectSprite::QuickSet(Texture* texture, TileObject* owner, int row, int column, int max_row, int max_column)
{
	texture_ = texture;
	owner_ = owner;
	base_pos_ = Vector2{ (texture->get_width() / max_column) * static_cast<double>(column), (texture_->get_height() / max_row) * static_cast<double>(row) };
	scale_ = Vector2{ texture->get_width() / static_cast<double>(max_column), texture_->get_height() / static_cast<double>(max_row) };
}
void TileObjectSprite::QuickSet(Texture* texture, TileObject* owner, Vector2 base_pos, Vector2 scale)
{
	texture_ = texture;
	owner_ = owner;
	base_pos_ = base_pos;
	scale_ = scale;
}
void TileObjectSprite::Render(ID3D11Device* p_d3d_device)
{

	if (owner_ && texture_) {
		DrawTexture(p_d3d_device, WorldToRenderPos(owner_->get_pos() - owner_->get_scale() / 2.f), owner_->get_scale(), base_pos_, scale_, texture_);
	}
}
