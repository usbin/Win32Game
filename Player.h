#pragma once
#include "RealObject.h"
#include "IItem.h"
class Texture;
class PlayerControlComponent;
class PhysicsComponent;
class ISprite;
class PlayerItemHolder;

class Player : public RealObject
{
public:
	Player();
	//Player(const Player& origin)
	//	:GObject(origin)
	//	,//추가로 초기화할것{
	//}
	virtual ~Player() override;


private:
	float speed_ = 0;
	PLAYER_STATE state_ = PLAYER_STATE::IDLE;
	PLAYER_HAND_STATE hand_state_ = PLAYER_HAND_STATE::NONE;

	std::vector<ItemData> inventory_; //[아이템코드, 개수]
	
	virtual void CreateCollider() override;
	virtual void CreateInteractor() override;
	virtual void CreateControlCmp() override;
	virtual void CreatePhysicsCmp() override;
	virtual void CreateRenderCmp() override;
	void CreateItemHolder();

	virtual void Update() override;
	virtual void Render(ID3D11Device* p_d3d_device) override;
	virtual void OnCollisionEnter(Collider* collider) override;
	virtual void OnCollisionStay(Collider* collider) override;
	virtual void OnCollisionExit(Collider* collider) override;
	void OnHold(const IItem* item);
	void OnUnhold();
	virtual void OnUseItem(ITEM_CODE item_code) override;
	const IItem* GetHoldItem();

public:
	inline const std::vector<ItemData>& get_inventory() { return inventory_; };
	
	friend class PlayerControlComponent;
	friend class PlayerRenderComponent;
	friend class PlayerItemHolder;
	
};

