#include "ItemSprite.h"
#include "IItem.h"
#include "Texture.h"
ItemSprite::ItemSprite()
{
}

ItemSprite::ItemSprite(ItemSprite& org)
	: texture_(org.texture_)
	, base_pos_(org.base_pos_)
	, scale_(org.scale_)
	, owner_(org.owner_)
{
}

ItemSprite::~ItemSprite()
{
}
void ItemSprite::QuickSet(Texture* texture, IItem* owner, int row, int column, int max_row, int max_column)
{
	texture_ = texture;
	owner_ = owner;
	base_pos_ = Vector2{ (texture->get_width() / max_column) * static_cast<double>(column), (texture_->get_height() / max_row) * static_cast<double>(row) };
	scale_ = Vector2{ texture->get_width() / static_cast<double>(max_column), texture_->get_height() / static_cast<double>(max_row) };
}

void ItemSprite::QuickSet(Texture* texture, IItem* owner, Vector2 base_pos, Vector2 scale)
{
	texture_ = texture;
	owner_ = owner;
	base_pos_ = base_pos;
	scale_ = scale;
}

void ItemSprite::Render(ID3D11Device* p_d3d_device)
{
}