#pragma once
#include "GObject.h"
class Texture;

class Player : public GObject
{
private:
	float speed_;
	
	virtual void CreateCollider() override;
	virtual void CreateAnimator() override;

public:
	Player();
	//Player(const Player& origin)
	//	:GObject(origin)
	//	,//�߰��� �ʱ�ȭ�Ұ�{

	//}
	virtual ~Player() override {};
	void Update() override;
	void Render(HDC hdc) override;
	virtual void OnCollisionEnter(const Collider& collider) override;
	virtual void OnCollisionStay(const Collider& collider) override;
	virtual void OnCollisionExit(const Collider& collider) override;

};

