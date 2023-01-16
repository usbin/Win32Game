#include "Player.h"

#include "KeyManager.h"
#include "Time.h"
#include "Missile.h"
#include "SceneManager.h"
#include "Texture.h"
#include "Collider.h"
#include "RealObjectAnimator.h"
#include "PathManager.h"
#include "Interactor.h"
#include "PlayerControlComponent.h"
#include "PhysicsComponent.h"
#include "GObjectSprite.h"
#include "RealObjectSprite.h"
#include "PlayerRenderComponent.h"
#include "PlayerItemHolder.h"
#include "ItemDb.h"
#include "Inventory.h"
#include "DropItem.h"
#include "ItemLooter.h"

Player::Player()
	: speed_(200.f){

	set_scale(Vector2{ 48, 96 });

	state_ = PLAYER_STATE::IDLE;
	set_direction(DIRECTION::DOWN);


	CreateCollider();
	CreateInteractor();
	CreateControlCmp();
	CreatePhysicsCmp();
	CreateRenderCmp();
	CreateItemHolder();
	CreateInventory();
	CreateItemLooter();


}
Player::~Player()
{
	delete inventory_;
	delete item_looter_;
}
void Player::Update()
{
	
	if(item_looter_) item_looter_->Update();

	if (KEY_DOWN(KEY::SPACE)) {
		
		//상호작용
		const std::vector<Interactor*>& interactors = get_interactor()->get_interactors();
		if (!interactors.empty()) {
			GObject* obj = interactors[0]->get_owner();
			obj->OnInteract(this);
		}
		
	}


}

void Player::Render(ID3D11Device* p_d3d_device)
{
	RealObject::Render(p_d3d_device);
	ComponentRender(p_d3d_device);
}


void Player::CreateCollider()
{
	Collider* collider = DEBUG_NEW Collider();
	collider->set_owner(this);
	collider->set_scale(Vector2{ 40, 40 });
	collider->set_is_physical_collider(true);
	collider->set_pos_offset(Vector2{ 0, 30 });
	set_collider(collider);
}


void Player::CreateInteractor()
{
	Interactor* interactor = DEBUG_NEW Interactor();
	interactor->Init(this, Vector2(0, 0), Vector2(100, 100));
	CreateGObject(interactor, GROUP_TYPE::INTERACTOR);
	set_interactor(interactor);
	
}

void Player::CreateControlCmp()
{
	control_cmp_ = DEBUG_NEW PlayerControlComponent();
}

void Player::CreatePhysicsCmp()
{
	physics_cmp_ = DEBUG_NEW PhysicsComponent();
}

void Player::CreateRenderCmp()
{
	render_cmp_ = DEBUG_NEW PlayerRenderComponent(this);

}

void Player::CreateItemHolder()
{
	item_holder_ = DEBUG_NEW PlayerItemHolder();
	item_holder_->set_owner(this);

}

void Player::CreateInventory()
{
	Inventory* inventory = DEBUG_NEW Inventory();
	inventory->Init(this);
	inventory_ = inventory;
}

void Player::CreateItemLooter()
{
	ItemLooter* item_looter = DEBUG_NEW ItemLooter();
	item_looter->Init(this, get_collider()->get_pos_offset());
	item_looter_ = item_looter;

}

void Player::OnCollisionEnter(Collider* collider)
{
}

void Player::OnCollisionStay(Collider* collider)
{
}

void Player::OnCollisionExit(Collider* collider)
{
}

void Player::OnHold(const IItem* item)
{
	switch (item->get_item_code())
	{
	case (int)ITEM_CODE::HOE:
	case (int)ITEM_CODE::WATERING_POT:
	case (int)ITEM_CODE::PICKAXE:
	case (int)ITEM_CODE::AXE:
		hand_state_ = PLAYER_HAND_STATE::NONE;
		break;
	case (int)ITEM_CODE::STONE:
	case (int)ITEM_CODE::WOOD:
	case (int)ITEM_CODE::WEED:
	case (int)ITEM_CODE::PARSNIP_SEED:
	case (int)ITEM_CODE::PARSNIP:
		hand_state_ = PLAYER_HAND_STATE::HOLD;
		break;
	}
}

void Player::OnUnhold()
{
	hand_state_ = PLAYER_HAND_STATE::NONE;
}

const IItem* Player::GetHoldItem()
{
	if (!item_holder_) return nullptr;
	else {
		return item_holder_->get_item();
	}
}

void Player::LootItem(DropItem* item)
{
	if (inventory_ && item) {
		inventory_->AddItem(item->get_item(), item->get_amount());
	}
}

void Player::OnUseItem(ITEM_CODE item_code) {
	if (!get_render_component()) return;
	get_render_component()->PlayItemAnimation(item_code);
	switch (item_code)
	{
	case ITEM_CODE::HOE:
	{
	} break;
	case ITEM_CODE::WATERING_POT:
		break;
	case ITEM_CODE::PICKAXE:
		break;
	case ITEM_CODE::AXE:
		break;
	case ITEM_CODE::STONE:
		break;
	case ITEM_CODE::WOOD:
		break;
	case ITEM_CODE::WEED:
		break;
	case ITEM_CODE::PARSNIP_SEED:
		break;
	case ITEM_CODE::PARSNIP:
		break;
	case ITEM_CODE::END:
		break;
	default:
		break;
	}
}

