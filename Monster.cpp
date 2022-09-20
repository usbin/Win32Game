#include "pch.h"
#include "Monster.h"
#include "Time.h"
#include "Collider.h"
#include "SelectGdi.h"

Monster::Monster()
	: move_speed_(200.f)
	, center_pos_(Vector2{0,0})
	, direction_(-1)
	, move_range_(0){
	Collider* collider = new Collider();
	collider->set_owner(this);
	collider->set_scale(Vector2{ 20, 20 });
	set_collider(collider);
}
Monster::~Monster() {};
void Monster::Update()
{
	//매 프레임 center-100에 도달할 때까지 pos.x-= move_speed_*dt
	//도달하면 center+100에 도달할 때까지 posx+= move_speed_*dt
	Vector2 pos = get_pos();
	if (abs(center_pos_.x - pos.x) > move_range_) {
		//가장자리로 바로잡기
		pos.x = center_pos_.x + direction_ * move_range_;
		direction_ *= -1;
	}
	pos.x = static_cast<float>(static_cast<double>(pos.x) + static_cast<double>(direction_ * move_speed_ * Time::GetInstance()->dt_f()));
	set_pos(pos);
}

void Monster::Render(HDC hdc) {
	SelectGdi _(hdc, BRUSH_TYPE::HOLLOW);

	Rectangle(hdc
		, static_cast<int>(get_pos().x - get_scale().x/2.)
		, static_cast<int>(get_pos().y - get_scale().y / 2.)
		, static_cast<int>(get_pos().x + get_scale().x / 2.)
		, static_cast<int>(get_pos().y + get_scale().y / 2.));

}
