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
Player::Player()
	: speed_(200.f) {
	
	CreateCollider();
	CreateAnimator();
	CreateInteractor();
	//애니메이션 시작
	get_animator()->Play(_T("Idle"));

}
void Player::Update()
{
	Vector2 v = get_pos();

	Vector2 move_direction{ 0, 0 };
	if (KEY_HOLD(KEY::RIGHT)) {
		move_direction.x = 1;
		set_direction(DIRECTION::RIGHT);
	}
	else if (KEY_HOLD(KEY::LEFT)) {
		move_direction.x = -1;
		set_direction(DIRECTION::LEFT);
	}
	if (KEY_HOLD(KEY::UP)) {
		move_direction.y = -1;
	}
	else if (KEY_HOLD(KEY::DOWN)) {
		move_direction.y = 1;
	}

	v.x += static_cast<float>(move_direction.Normalize().x * speed_ * Time::GetInstance()->dt_f());
	v.y += static_cast<float>(move_direction.Normalize().y * speed_ * Time::GetInstance()->dt_f());
	
	set_pos(v);

	if (KEY_DOWN(KEY::SPACE)) {
		
		//상호작용
		const std::vector<Interactor*>& interactors = get_interactor()->get_interactors();
		if (!interactors.empty()) {
			GObject* obj = interactors[0]->get_owner();
			obj->OnInteract(this);
		}
	}

	if (KEY_DOWN(KEY::Q)) {
		ChangeScene(SCENE_TYPE::SCENE_01);
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
	set_collider(collider);
}

void Player::CreateAnimator()
{
	Texture* texture = ResManager::GetInstance()->LoadTexture(_T("player"), _T("texture\\MapleStory_Kino-Smaller.png"));
	Animator* animator = new RealObjectAnimator();
	animator->CreateAnimation(
		_T("Idle")
		, texture
		, Vector2{ 0, 0 }
		, Vector2{ 42, 42 }
		, Vector2{ 42, 0 }
		, Vector2{ 0, -15 }
		, 0.1f
		, 4
		, true);
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

void Player::OnCollisionEnter(Collider* collider)
{
}

void Player::OnCollisionStay(Collider* collider)
{
}

void Player::OnCollisionExit(Collider* collider)
{
}


