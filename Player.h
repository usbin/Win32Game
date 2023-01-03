#pragma once
#include "RealObject.h"

class Texture;
class PlayerControlComponent;
class PhysicsComponent;
class Sprite;

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
	PLAYER_STATE state_;
	
	virtual void CreateCollider() override;
	virtual void CreateInteractor() override;
	virtual void CreateControlCmp() override;
	virtual void CreatePhysicsCmp() override;
	virtual void CreateRenderCmp() override;

	virtual void Update() override;
	virtual void Render(ID3D11Device* p_d3d_device) override;
	virtual void OnCollisionEnter(Collider* collider) override;
	virtual void OnCollisionStay(Collider* collider) override;
	virtual void OnCollisionExit(Collider* collider) override;


	
	
	friend class PlayerControlComponent;
	friend class PlayerRenderComponent;
	
};

