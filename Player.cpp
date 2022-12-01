#include "Player.h"

#include "KeyManager.h"
#include "Time.h"
#include "Missile.h"
#include "SceneManager.h"
#include "Texture.h"
#include "Collider.h"
#include "Animator.h"
#include "PathManager.h"

Player::Player()
	: speed_(200.f) {
	
	CreateCollider();
	CreateAnimator();
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
		set_direction(DIRECTION::UP);
	}
	else if (KEY_HOLD(KEY::DOWN)) {
		move_direction.y = 1;
		set_direction(DIRECTION::DOWN);
	}

	v.x += static_cast<float>(move_direction.Normalize().x * speed_ * Time::GetInstance()->dt_f());
	v.y += static_cast<float>(move_direction.Normalize().y * speed_ * Time::GetInstance()->dt_f());
	
	set_pos(v);

	if (KEY_DOWN(KEY::SPACE)) {
		Missile* m = new Missile();
		Vector2 pos = get_pos();
		m->set_pos(pos);
		m->set_scale(Vector2{ 4, 4 });
		m->set_speed(200.f);
		m->set_direction(Vector2{0, -1});
		m->set_group_type(GROUP_TYPE::MISSILE);
		CreateGObject(m, GROUP_TYPE::MISSILE);
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
	Animator* animator = new Animator();
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

void Player::OnCollisionEnter(const Collider& collider)
{
}

void Player::OnCollisionStay(const Collider& collider)
{
}

void Player::OnCollisionExit(const Collider& collider)
{
}


