#include "Crop.h"
#include "RealObject.h"
#include "IItemHolder.h"
#include "FieldTileObject.h"
#include "ItemSprite.h"
#include "SceneManager.h"
Crop::~Crop()
{
    delete sprite_;
    sprite_ = nullptr;
}

IItem* Crop::Init(int item_code, tstring name)
{
    item_code_ = item_code;
    name_ = name;
    

    
    return this;
}

bool Crop::Use(RealObject* obj) const
{
    switch (item_code_) {
    case (int)ITEM_CODE::PARSNIP: { // 순무
    } break;
    }
    return false;

    
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
    if (sprite_ && holder && holder->get_owner()) {
        DrawTexture(p_d3d_device, WorldToRenderPos(holder->get_owner()->get_pos() + holder->get_hold_offset() + crop_hold_offset_) - crop_hold_scale_/2.f, crop_hold_scale_
            , sprite_->get_base_pos(), sprite_->get_scale(), sprite_->get_texture(), RENDER_LAYER::TOP);
    }
}


void Crop::OnHold(RealObject* owner) const
{
    // 선택돼있을 때(캐릭터가 잡고 있을 때)
}
