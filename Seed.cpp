#include "Seed.h"
#include "RealObject.h"
#include "IItemHolder.h"
#include "SceneManager.h"
#include "FieldTileObject.h"
#include "ItemDb.h"
#include "Seed.h"
#include "ItemSprite.h"

Seed::~Seed()
{
    delete sprite_;
    sprite_ = nullptr;
    for (int i = 0; i <= max_level_; i++) {
        delete sprites_[i];
    }
}

IItem* Seed::Init(int item_code, int crop_code, UINT max_level, tstring name)
{
    item_code_ = item_code;
    name_ = name;
    crop_code_ = crop_code;

    max_level_ = max_level;
    for (int i = 0; i <= max_level; i++) {
        sprites_.push_back(nullptr);
    }

    switch (item_code) {
    case (int)ITEM_CODE::PARSNIP: {

    } break;
    }

    return this;
}

void Seed::OnHold(RealObject* owner) const
{
}

int Seed::get_item_code() const
{
    return item_code_;
}

bool Seed::Use(RealObject* obj) const
{
    if (obj->get_item_holder()) {

        TileObject* tile_object;
        Vector2 out_pos;

        SceneManager::GetInstance()->get_current_scene()->GetTileObject(obj->get_item_holder()->get_target_pos(), out_pos, tile_object);
        if (!tile_object) return false;
        FieldTileObject* field_tile_object = dynamic_cast<FieldTileObject*>(tile_object);
        if (!field_tile_object) return false;
        field_tile_object->SetSeed(this, 0);
        return true;
    }
    return false;
}

void Seed::UpdateOnHolder(IItemHolder* holder) const
{
}

void Seed::RenderOnHolder(IItemHolder* holder, ID3D11Device* p_d3d_device) const
{
    if (sprite_ && holder && holder->get_owner()) {
        Vector2 item_hold_offset{ 0, -40 };
        DrawTexture(p_d3d_device, WorldToRenderPos(holder->get_owner()->get_pos() + holder->get_hold_offset() + item_hold_offset - holder->get_hold_scale()/2.f), holder->get_hold_scale()
            , sprite_->get_base_pos(), sprite_->get_scale(), sprite_->get_texture(), RENDER_LAYER::TOP);
    }
}


void Seed::UpdateOnField(FieldTileObject* field_tile_object) const
{
}

void Seed::RenderOnField(FieldTileObject* field_tile_object, ID3D11Device* p_d3d_device) const
{
    ItemSprite* sprite = sprites_[field_tile_object->get_level()];
    if (sprite) {
        DrawTexture(p_d3d_device, WorldToRenderPos(field_tile_object->get_pos() - field_tile_object->get_scale() / 2.f), field_tile_object->get_scale()
            , sprite->get_base_pos(), sprite->get_scale(), sprite->get_texture());
    }

}