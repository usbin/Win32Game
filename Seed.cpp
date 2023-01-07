#include "Seed.h"
#include "RealObject.h"
#include "IItemHolder.h"
Seed::~Seed()
{
    delete sprite_;
}

IItem* Seed::Init(int item_code, tstring name)
{
    item_code_ = item_code;
    name_ = name;

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

void Seed::Use(RealObject* obj) const
{
    int a = 0;
}

void Seed::UpdateOnHolder(IItemHolder* holder) const
{
}

void Seed::RenderOnHolder(IItemHolder* holder, ID3D11Device* p_d3d_device) const
{
}

