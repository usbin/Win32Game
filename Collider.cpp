#include "Collider.h"
#include "GObject.h"
#include "SelectGDI.h"


UINT Collider::id_counter_ = 1;

Collider::Collider()
	: id_(id_counter_++)
	, pos_offset_{}
	, scale_{}
	, owner_(nullptr)
	, is_physical_collider_(false)
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
	, is_physical_collider_(false)
{
}

void Collider::FinalUpdate()
{
	//owner의 위치를 따라감.
	final_pos_ = owner_->get_pos() + pos_offset_;

}


void Collider::Render(ID3D11Device* p_d3d_device)
{
	
	Vector2 render_pos = WorldToRenderPos(final_pos_);



#ifdef _DEBUG

	DrawRectangle(p_d3d_device, render_pos - get_scale() / 2.f, get_scale(), ARGB(0xFF0000FF), 1);
#endif
	
}

void Collider::OnCollisionEnter(Collider* collider)
{
	if (collider->get_is_physical_collider() && is_physical_collider_) {
		physical_collisions_.push_back(collider);
	}
	owner_->OnCollisionEnter(collider);
	
}

void Collider::OnCollisionStay(Collider* collider)
{
	owner_->OnCollisionStay(collider);
}

void Collider::OnCollisionExit(Collider* collider)
{
	if (collider->get_is_physical_collider() && is_physical_collider_) {
		physical_collisions_.erase(std::remove(physical_collisions_.begin(), physical_collisions_.end(), collider), physical_collisions_.end());
	}
	owner_->OnCollisionExit(collider);
}

