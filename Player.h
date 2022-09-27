#pragma once
#include "RealObject.h"
class Texture;

class Player : public RealObject
{
private:
	float speed_;
	
	virtual void CreateCollider() override;
	virtual void CreateAnimator() override;

public:
	Player();
	//Player(const Player& origin)
	//	:GObject(origin)
	//	,//추가로 초기화할것{

	//}
	virtual ~Player() override {};
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void OnCollisionEnter(const Collider& collider) override;
	virtual void OnCollisionStay(const Collider& collider) override;
	virtual void OnCollisionExit(const Collider& collider) override;

};

