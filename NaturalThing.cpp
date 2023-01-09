#include "NaturalThing.h"
#include "TileObjectSprite.h"
#include "TileObject.h"
NaturalThing::~NaturalThing()
{
	delete sprite_;
}
void NaturalThing::Init(TILE_OBJECT_TYPE type, tstring name, TileObjectSprite* sprite)
{
	type_ = type;
	name_ = name;

	sprite_ = sprite;
}

void NaturalThing::Update(TileObject* tile_object) const
{
}

void NaturalThing::Render(TileObject* tile_object, ID3D11Device* p_d3d_device) const
{
	if (sprite_) {
			
		DrawTexture(p_d3d_device, WorldToRenderPos(tile_object->get_pos() - tile_object->get_scale() / 2.f), tile_object->get_scale()
			, sprite_->get_base_pos(), sprite_->get_scale(), sprite_->get_texture());

	}
}
