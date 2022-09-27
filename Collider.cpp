#include "Collider.h"
#include "GObject.h"
#include "SelectGDI.h"


UINT Collider::id_counter_ = 1;

Collider::Collider()
	: id_(id_counter_++)
	, pos_offset_{}
	, scale_{}
	, owner_(nullptr)
	, collision_count_(0)
{
}

Collider::~Collider()
{
}

Collider::Collider(const Collider& org)
	: id_(id_counter_++)
	, pos_offset_{org.pos_offset_}
	, scale_{org.scale_}
	, owner_(nullptr)
	, collision_count_(0)
{
}

void Collider::FinalUpdate()
{
	//owner의 위치를 따라감.
	final_pos_ = owner_->get_pos() + pos_offset_;

}


void Collider::Render(HDC hdc)
{
	//테두리 그리기
	PEN_TYPE pen_type = PEN_TYPE::GREEN;
	if (collision_count_) pen_type = PEN_TYPE::RED;
	SelectGdi _(hdc, pen_type);
	SelectGdi __(hdc, BRUSH_TYPE::HOLLOW);

	Vector2 render_pos = WorldToRenderPos(final_pos_);
	Rectangle(hdc
		, static_cast<int>(render_pos.x - scale_.x / 2)
		, static_cast<int>(render_pos.y - scale_.y / 2)
		, static_cast<int>(render_pos.x + scale_.x / 2)
		, static_cast<int>(render_pos.y + scale_.y / 2));
}

void Collider::OnCollisionEnter(const Collider& collider)
{
	collision_count_++;
	owner_->OnCollisionEnter(collider);
}

void Collider::OnCollisionStay(const Collider& collider)
{
	owner_->OnCollisionStay(collider);
}

void Collider::OnCollisionExit(const Collider& collider)
{
	collision_count_--;
	owner_->OnCollisionExit(collider);
}
