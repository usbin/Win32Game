#pragma once
#include "RealObject.h"
#include "IItem.h"
class Texture;
class PlayerControlComponent;
class PhysicsComponent;
class ISprite;
class PlayerItemHolder;
class ItemData;
class Inventory;
class DropItem;
class ItemLooter;
class Player : public RealObject
{
public:
	Player();
	virtual ~Player() override;


private:
	float speed_ = 0;
	PLAYER_STATE state_ = PLAYER_STATE::IDLE;
	PLAYER_HAND_STATE hand_state_ = PLAYER_HAND_STATE::NONE;
	Inventory* inventory_ = nullptr;
	ItemLooter* item_looter_ = nullptr;
	
	virtual void CreateCollider() override;
	virtual void CreateInteractor() override;
	virtual void CreateControlCmp() override;
	virtual void CreatePhysicsCmp() override;
	virtual void CreateRenderCmp() override;
	void CreateItemHolder();
	void CreateInventory();
	void CreateItemLooter();

	virtual void Update() override;
	virtual void Render(ID3D11Device* p_d3d_device) override;
	virtual void OnCollisionEnter(Collider* collider) override;
	virtual void OnCollisionStay(Collider* collider) override;
	virtual void OnCollisionExit(Collider* collider) override;
	void OnHold(const IItem* item);
	void OnUnhold();
	virtual void OnUseItem(ITEM_CODE item_code) override;
	const IItem* GetHoldItem();
	void LootItem(DropItem* item);

public:
	inline Inventory* get_inventory() const { return inventory_; };
	virtual void MoveTo(GObject* gobject) override;
	
	friend class PlayerControlComponent;
	friend class PlayerRenderComponent;
	friend class PlayerItemHolder;
	
};

