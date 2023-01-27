#include "Vender.h"
#include "Interactor.h"
#include "ShopUi.h"
#include "Player.h"
void Vender::Init()
{
	CreateInteractor();
}

void Vender::CreateInteractor()
{
	Interactor* itr = DEBUG_NEW Interactor();
	itr->Init(this, Vector2::Zero(), get_scale());
	CreateGObject(itr, GROUP_TYPE::INTERACTOR);
	set_interactor(itr);
}

void Vender::Update()
{
}

void Vender::OnInteract(const GObject* obj)
{
	//¼¥ ¿­±â
	const Player* player = dynamic_cast<const Player*>(obj);
	if (player) {
		ShopUi* shop = DEBUG_NEW ShopUi(true);
		shop->set_group_type(GROUP_TYPE::UI);
		shop->Init(player);
		CreateGObject(shop, GROUP_TYPE::UI);
	}
	

}
