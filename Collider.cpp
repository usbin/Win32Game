#include "Collider.h"
#include "GObject.h"
#include "SelectGDI.h"


UINT Collider::id_counter_ = 1;

Collider::Collider()
	: id_(id_counter_++)
	, pos_offset_{}
	, scale_{}
	, owner_(nullptr)
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

	DrawRectangle(p_d3d_device, render_pos - get_scale() / 2.f, get_scale(), ARGB(0xFF0000FF));
#endif
	
}

void Collider::OnCollisionEnter(Collider* collider)
{
	owner_->OnCollisionEnter(collider);
}

void Collider::OnCollisionStay(Collider* collider)
{
	owner_->OnCollisionStay(collider);
}

void Collider::OnCollisionExit(Collider* collider)
{
	owner_->OnCollisionExit(collider);
}


void Collider::SaveToFile(FILE* p_file) {

	fwrite(&pos_offset_, sizeof(Vector2), 1, p_file);
	fwrite(&scale_, sizeof(Vector2), 1, p_file);
	fwrite(&final_pos_, sizeof(Vector2), 1, p_file);
}

void Collider::LoadFromFile(FILE* p_file)
{
	fread(&pos_offset_, sizeof(Vector2), 1, p_file);
	fread(&scale_, sizeof(Vector2), 1, p_file);
	fread(&final_pos_, sizeof(Vector2), 1, p_file);
}
