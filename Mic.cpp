#include "Mic.h"

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

void Mic::OnHold(GObject* owner)
{
}

int Mic::get_item_code()
{
    return item_code_;
}
