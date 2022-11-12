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
	//화면을 벗어나면 소멸
	if (pos.x < 0 || pos.y < 0
		|| Core::GetInstance()->get_pt_resolution().x < pos.x || Core::GetInstance()->get_pt_resolution().y < pos.y) {
		DeleteGObject(this, get_group_type());
	}

	//direction 방향으로 speed_*dt만큼 날아감
	pos.x += static_cast<float>(static_cast<double>(direction_.x) * speed_ * Time::GetInstance()->dt_f());
	pos.y += static_cast<float>(static_cast<double>(direction_.y) * speed_ * Time::GetInstance()->dt_f());
	set_pos(pos);
	


}

void Missile::Render(LPDIRECT3DDEVICE9 p_d3d_device)
{
	RealObject::Render(p_d3d_device);

	/*Vector2 render_pos = WorldToRenderPos(get_pos());
	Ellipse(hdc
		, static_cast<int>(render_pos.x - get_scale().x/2.)
		, static_cast<int>(render_pos.y - get_scale().y / 2.)
		, static_cast<int>(render_pos.x + get_scale().x / 2.)
		, static_cast<int>(render_pos.y + get_scale().y / 2.));
	*/
	ComponentRender(p_d3d_device);
}

void Missile::OnCollisionEnter(const Collider& collider)
{
	DeleteGObject(this, get_group_type());
}
