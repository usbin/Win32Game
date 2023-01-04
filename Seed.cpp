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
    // 선택돼있을 때(캐릭터가 잡고 있을 때)
    owner->get_item_holder()->SetItem(this);
}

int Seed::get_item_code() const
{
    return item_code_;
}

void Seed::Use(RealObject* obj)
{
}
