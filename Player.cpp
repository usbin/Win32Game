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
#include "Sprite.h"
#include "RealObjectSprite.h"
#include "PlayerRenderComponent.h"

Player::Player()
	: speed_(200.f){

	set_scale(Vector2{ 32, 64 });

	state_ = PLAYER_STATE::IDLE;
	set_direction(DIRECTION::DOWN);


	CreateCollider();
	CreateAnimator();
	CreateInteractor();
	CreateControlCmp();
	CreatePhysicsCmp();
	CreateRenderCmp();


}
Player::~Player()
{
}
void Player::Update()
{
	

	if (KEY_DOWN(KEY::SPACE)) {
		
		//��ȣ�ۿ�
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
	Collider* collider = new Collider();
	collider->set_owner(this);
	collider->set_scale(Vector2{ 20, 20 });
	collider->set_is_physical_collider(true);
	collider->set_pos_offset(Vector2{ 0, 20 });
	set_collider(collider);
}

void Player::CreateAnimator()
{
	Texture* texture = ResManager::GetInstance()->LoadTexture(_T("player"), _T("texture\\StardewValley_Player.png"));
	Animator* animator = new RealObjectAnimator();
	animator->CreateAnimation(
		_T("Walk_Front")
		, texture
		, Vector2{ 16, 0 }
		, Vector2{ 16, 32 }
		, Vector2{ 16, 0 }
		, Vector2{ 0, 0 }
		, .2f
		, 3
		, false);
	animator->CreateAnimation(
		_T("Walk_Back")
		, texture
		, Vector2{ 16, 64 }
		, Vector2{ 16, 32 }
		, Vector2{ 16, 0 }
		, Vector2{ 0, 0 }
		, .2f
		, 3
		, false);
	animator->CreateAnimation(
		_T("Walk_Right")
		, texture
		, Vector2{ 16, 32 }
		, Vector2{ 16, 32 }
		, Vector2{ 16, 0 }
		, Vector2{ 0, 0 }
		, .2f
		, 3
		, false);
	animator->CreateAnimation(
		_T("Walk_Left")
		, texture
		, Vector2{ 16, 32 }
		, Vector2{ 16, 32 }
		, Vector2{ 16, 0 }
		, Vector2{ 0, 0 }
		, .2f
		, 3
		, false);
	animator->CreateAnimation(
		_T("Hold_And_Walk_Front")
		, texture
		, Vector2{ 112, 0 }
		, Vector2{ 16, 32 }
		, Vector2{ 16, 0 }
		, Vector2{ 0, 0 }
		, .2f
		, 3
		, false);
	animator->CreateAnimation(
		_T("Hold_And_Walk_Back")
		, texture
		, Vector2{ 112, 64 }
		, Vector2{ 16, 32 }
		, Vector2{ 16, 0 }
		, Vector2{ 0, 0 }
		, .2f
		, 3
		, false);
	animator->CreateAnimation(
		_T("Hold_And_Walk_Right")
		, texture
		, Vector2{ 112, 32 }
		, Vector2{ 16, 32 }
		, Vector2{ 16, 0 }
		, Vector2{ 0, 0 }
		, .2f
		, 3
		, false);
	animator->CreateAnimation(
		_T("Hold_And_Walk_Left")
		, texture
		, Vector2{ 112, 32 }
		, Vector2{ 16, 32 }
		, Vector2{ 16, 0 }
		, Vector2{ 0, 0 }
		, .2f
		, 3
		, false);
	animator->set_owner(this);
	set_animator(animator);
}

void Player::CreateInteractor()
{
	Interactor* interactor = new Interactor();
	interactor->Init(this, Vector2(0, 0), Vector2(100, 100));
	CreateGObject(interactor, GROUP_TYPE::INTERACTOR);
	set_interactor(interactor);
	
}

void Player::CreateControlCmp()
{
	control_cmp_ = new PlayerControlComponent();
}

void Player::CreatePhysicsCmp()
{
	physics_cmp_ = new PhysicsComponent();
}

void Player::CreateRenderCmp()
{
	render_cmp_ = new PlayerRenderComponent(this);

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


