#include "Crop.h"
#include "RealObject.h"
#include "IItemHolder.h"
#include "FieldTileObject.h"
#include "ItemSprite.h"
Crop::~Crop()
{
    delete sprite_;
    sprite_ = nullptr;
    for (int i = 0; i <= max_level_; i++) {
        delete sprites_[i];
    }
}

IItem* Crop::Init(int item_code, tstring name, UINT max_level)
{
    item_code_ = item_code;
    name_ = name;
    max_level_ = max_level;
    for (int i = 0; i <= max_level; i++) {
        sprites_.push_back(nullptr);
    }

    
    return this;
}

void Crop::Use(RealObject* obj) const
{
    switch (item_code_) {
    case (int)ITEM_CODE::PARSNIP: { // 순무

    } break;
    }

    
}

int Crop::get_item_code() const
{
    return item_code_;
}


void Crop::UpdateOnHolder(IItemHolder* holder) const
{
}

void Crop::RenderOnHolder(IItemHolder* holder, ID3D11Device* p_d3d_device) const
{
}

void Crop::UpdateOnField(FieldTileObject* field_tile_object) const
{
}

void Crop::RenderOnField(FieldTileObject* field_tile_object, ID3D11Device* p_d3d_device) const
{
    ItemSprite* sprite = sprites_[field_tile_object->get_level()];
    if (sprite) {
        DrawTexture(p_d3d_device, WorldToRenderPos(field_tile_object->get_pos() - field_tile_object->get_scale() / 2.f), field_tile_object->get_scale()
            , sprite->get_base_pos(), sprite->get_scale(), sprite->get_texture());
    }

}

void Crop::OnHold(RealObject* owner) const
{
    // 선택돼있을 때(캐릭터가 잡고 있을 때)
}
