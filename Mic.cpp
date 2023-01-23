#include "Mic.h"
#include "RealObject.h"
#include "IItemHolder.h"
#include "ItemSprite.h"

Mic::~Mic()
{
    delete sprite_;
    delete profile_sprite_;
}

IItem* Mic::Init(int item_code, tstring name, tstring description, UINT price)
{
    item_code_ = item_code;
    name_ = name;
    price_ = price;
    description_ = description;
    switch (item_code) {
    case (int)ITEM_CODE::STONE: {

    } break;
    case (int)ITEM_CODE::WEED: {

    } break;
    case (int)ITEM_CODE::WOOD: {

    } break;
    }

    return this;
}

void Mic::OnHold(RealObject* owner) const
{
}

int Mic::get_item_code() const
{
    return item_code_;
}

void Mic::UpdateOnHolder(IItemHolder* holder) const
{
}

void Mic::RenderOnHolder(IItemHolder* holder, ID3D11Device* p_d3d_device) const
{
    if (sprite_ && holder && holder->get_owner()) {
        DrawTexture(p_d3d_device, WorldToRenderPos(holder->get_owner()->get_pos() + holder->get_hold_offset() + item_hold_offset) - item_hold_scale / 2.f, item_hold_scale
            , sprite_->get_base_pos(), sprite_->get_scale(), sprite_->get_texture(), RENDER_LAYER::TOP);
    }
}

