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
    case (int)ITEM_CODE::PARSNIP: { // ����
    } break;
    }

    return this;
}

void Crop::Use(RealObject* obj)
{

}

int Crop::get_item_code() const
{
    return item_code_;
}

void Crop::OnHold(RealObject* owner) const
{
    // ���õ����� ��(ĳ���Ͱ� ��� ���� ��)
    owner->get_item_holder()->SetItem(this);
}
