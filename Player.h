#pragma once
#include "RealObject.h"
class Texture;

class Player : public RealObject
{
private:
	float speed_;
	
	virtual void CreateCollider() override;
	virtual void CreateAnimator() override;
	virtual void CreateInteractor() override;

public:
	Player();
	//Player(const Player& origin)
	//	:GObject(origin)
	//	,//�߰��� �ʱ�ȭ�Ұ�{

	//}
	virtual ~Player() override {};
	virtual void Update() override;
	virtual void Render(ID3D11Device* p_d3d_device) override;
	virtual void OnCollisionEnter(Collider* collider) override;
	virtual void OnCollisionStay(Collider* collider) override;
	virtual void OnCollisionExit(Collider* collider) override;

};

