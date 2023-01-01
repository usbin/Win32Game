#include "Seed.h"

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

void Seed::OnHold(GObject* owner)
{
}

int Seed::get_item_code()
{
    return item_code_;
}

void Seed::Use(GObject* obj)
{
}
