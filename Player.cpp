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
#include "IRenderComponent.h"

Player::Player()
	: speed_(200.f){

	set_scale(Vector2{ 32, 64 });

	state_ = PLAYER_STATE::IDLE;
	set_direction(DIRECTION::DOWN);


	CreateCollider();
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
	Collider* collider = new Collider();
	collider->set_owner(this);
	collider->set_scale(Vector2{ 20, 20 });
	collider->set_is_physical_collider(true);
	collider->set_pos_offset(Vector2{ 0, 20 });
	set_collider(collider);
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


