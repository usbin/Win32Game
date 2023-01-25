#include "ShippingBox.h"
#include "Interactor.h"
#include "RealObject.h"
#include "Player.h"
#include "PlayerItemHolder.h"
#include "ItemData.h"
#include "Crop.h"
#include "Inventory.h"
#include "RealObjectRenderComponent.h"
#include "RealObjectSprite.h"
#include "Texture.h"
#include "ResManager.h"
#include "Collider.h"
#include "Mic.h"
#include "FmodSound.h"
ShippingBox::~ShippingBox()
{
	SafeDeleteVector<const ItemData*>(items_);
}
void ShippingBox::Init()
{
	CreateRenderCmp();
	CreateInteractor();
	CreateCollider();
}
void ShippingBox::CreateRenderCmp()
{
	render_cmp_ = DEBUG_NEW RealObjectRenderComponent(this);
	Texture* texture = ResManager::GetInstance()->LoadTexture(_T("Stardew Valley Farm Spring"), _T("texture\\StardewValley_FarmSpring.png"));
	RealObjectSprite* sprite = DEBUG_NEW RealObjectSprite();
	sprite->QuickSet(texture, this, Vector2{ 192, 224 }, Vector2{ 32, 32 });
	render_cmp_->ChangeSprite(sprite);
}
void ShippingBox::CreateCollider()
{
	Collider* collider = DEBUG_NEW Collider();
	collider->set_is_physical_collider(true);
	collider->set_pos_offset(Vector2{ 0, 10 });
	collider->set_scale(get_scale() - Vector2{ 0, 10 });
	collider->set_owner(this);
	collider_ = collider;
}
void ShippingBox::CreateInteractor()
{
	Interactor* interactor = DEBUG_NEW Interactor();
	interactor->Init(this, Vector2{ 0, 0 }, get_scale());
	interactor->get_collider()->set_is_physical_collider(true);
	CreateGObject(interactor, GROUP_TYPE::INTERACTOR);
	set_interactor(interactor);
}

void ShippingBox::Update()
{

}

void ShippingBox::Render(ID3D11Device* p_d3d_device)
{
	render_cmp_->Render(this, p_d3d_device);
}

void ShippingBox::OnInteract(const GObject* req_obj)
{
	//req_obj의 아이템 홀더를 가져와, (아이템, 개수)만큼 내부에 집어넣음.
	if (req_obj) {
		const Player* player = dynamic_cast<const Player*>(req_obj);
		if (player) {
			PlayerItemHolder* item_holder = dynamic_cast<PlayerItemHolder*>( player->get_item_holder());
			if (item_holder) {
				int index = item_holder->GetHoldIndex();
				const ItemData* item_data = item_holder->GetItemData();
				//아이템이 작물일 때
				if (item_data 
					&& (dynamic_cast<const Crop*>(item_data->item)
						||dynamic_cast<const Mic*>(item_data->item))) {
					//출하상자에 넣고 인벤토리에서 제거
					items_.push_back(DEBUG_NEW ItemData{ item_data->item, item_data->amount });
					player->get_inventory()->RemoveItem(index, item_data->amount);
					//효과음 재생
					Sound* effect = ResManager::GetInstance()->LoadSound(_T("ShippingBox Effect"), _T("sound\\ShippingBox_Effect.wav"));
					FmodSound::GetInstance()->Play(FmodSound::GetInstance()->GetChannel(), effect, false);

				}
			}
		}
	}
}

UINT ShippingBox::CellItems()
{
	UINT gold = 0;
	for (const ItemData* item : items_) {
		gold += item->item->get_price() * item->amount;
	}
	SafeDeleteVector<const ItemData*>(items_);
	return gold;
}
