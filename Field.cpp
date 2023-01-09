#include "Field.h"
#include "TileObjectSprite.h"
#include "TileObject.h"
#include "Crop.h"
#include "FieldTileObject.h"
Field::~Field()
{
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 16; j++) {
			delete sprites_[i][j];
		}
	}
}
void Field::Init(TILE_OBJECT_TYPE type, tstring name)
{
	type_ = type;
	name_ = name;
	
	
}

void Field::SetSprite(bool is_watered, int field_connected, TileObjectSprite* sprite)
{
	delete sprites_[is_watered][field_connected];
	sprites_[is_watered][field_connected] = sprite;
}

void Field::Update(TileObject* tile_object) const
{
	
}

void Field::Render(TileObject* tile_object, ID3D11Device* p_d3d_device) const
{
	FieldTileObject* field_tile_object = dynamic_cast<FieldTileObject*>(tile_object);
	
	TileObjectSprite* field_sprite = sprites_[false][field_tile_object->get_field_connected()];
	TileObjectSprite* field_sprite_watered = sprites_[true][field_tile_object->get_water_connected()];
	if (field_sprite) {
		DrawTexture(p_d3d_device, WorldToRenderPos(tile_object->get_pos() - tile_object->get_scale() / 2.f), tile_object->get_scale()
			, field_sprite->get_base_pos(), field_sprite->get_scale(), field_sprite->get_texture());
		if (field_tile_object->is_watered()) {
			DrawTexture(p_d3d_device, WorldToRenderPos(tile_object->get_pos() - tile_object->get_scale() / 2.f), tile_object->get_scale()
				, field_sprite_watered->get_base_pos(), field_sprite_watered->get_scale(), field_sprite_watered->get_texture());
		}

	}

}
