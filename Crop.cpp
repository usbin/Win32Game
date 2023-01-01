#include "Crop.h"

IItem* Crop::Init(int item_code, tstring name)
{
    item_code_ = item_code;
    name_ = name;
    switch (item_code) {
    case (int)ITEM_CODE::PARSNIP: { // ¼ø¹«
    } break;
    }

    return this;
}

void Crop::Use(GObject* obj)
{

}

int Crop::get_item_code()
{
    return item_code_;
}

void Crop::OnHold(GObject* owner)
{
}
