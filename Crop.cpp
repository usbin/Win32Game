#include "Crop.h"
#include "RealObject.h"
#include "IItemHolder.h"
Crop::~Crop()
{
    delete sprite_;
}

IItem* Crop::Init(int item_code, tstring name)
{
    item_code_ = item_code;
    name_ = name;
    switch (item_code) {
    case (int)ITEM_CODE::PARSNIP: { // 순무
    } break;
    }

    return this;
}

void Crop::Use(RealObject* obj) const
{

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

void Crop::OnUnhold() const
{
}

void Crop::OnHold(RealObject* owner) const
{
    // 선택돼있을 때(캐릭터가 잡고 있을 때)
    owner->get_item_holder()->SetItem(this);
}
