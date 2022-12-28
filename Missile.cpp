#include "Missile.h"
#include "Time.h"
#include "Core.h"
#include "SceneManager.h"
#include "Collider.h"


Missile::Missile()
	: direction_(Vector2{ 0, 0 })
	, speed_(200.f) {
	Collider* collider = new Collider();
	collider->set_owner(this);
	collider->set_scale(Vector2{ 5, 5 });
	set_collider(collider);
}

void Missile::Update()
{
	Vector2 pos = get_pos();
	Vector2 render_pos = WorldToRenderPos(pos);
	//화면을 벗어나면 소멸
	if (render_pos.x < 0 || render_pos.y < 0
		|| Core::GetInstance()->get_pt_resolution().x < render_pos.x || Core::GetInstance()->get_pt_resolution().y < render_pos.y) {
		DeleteGObject(this, get_group_type());
	}

	//direction 방향으로 speed_*dt만큼 날아감
	pos.x += static_cast<float>(static_cast<double>(direction_.x) * speed_ * Time::GetInstance()->dt_f());
	pos.y += static_cast<float>(static_cast<double>(direction_.y) * speed_ * Time::GetInstance()->dt_f());
	set_pos(pos);
	
}

void Missile::Render(ID3D11Device* p_d3d_device)
{
	RealObject::Render(p_d3d_device);

	Vector2 render_pos = WorldToRenderPos(get_pos());
	DrawRectangle(p_d3d_device, render_pos - get_scale() / 2.f, get_scale(), ARGB(0xFF000000));
	
	ComponentRender(p_d3d_device);
}

void Missile::OnCollisionEnter(Collider* collider)
{
	DeleteGObject(this, get_group_type());
}
