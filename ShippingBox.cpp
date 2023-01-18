#include "ShippingBox.h"
#include "Interactor.h"
void ShippingBox::CreateInteractor()
{
	Interactor* interactor = DEBUG_NEW Interactor();
	interactor->Init(this, Vector2{ 0, 0 }, get_scale());
	CreateGObject(interactor, GROUP_TYPE::INTERACTOR);
	set_interactor(interactor);
}

void ShippingBox::Update()
{

}

void ShippingBox::OnInteract(const GObject* req_obj)
{
	//
}
