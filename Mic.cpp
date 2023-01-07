#include "Mic.h"
#include "RealObject.h"
#include "IItemHolder.h"
Mic::~Mic()
{
    delete sprite_;
}

IItem* Mic::Init(int item_code, tstring name)
{
    item_code_ = item_code;
    name_ = name;
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
}

