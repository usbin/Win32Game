#include "Interactor.h"
#include "KeyManager.h"
#include "Collider.h"
Interactor::Interactor()
{
	set_group_type(GROUP_TYPE::INTERACTOR);
}

Interactor::~Interactor()
{
}


void Interactor::Init(GObject* owner, Vector2 pos_offset, Vector2 scale)
{

	owner_ = owner;
	pos_offset_ = pos_offset;
	Collider* collider = new Collider();
	collider->set_owner(this);
	collider->set_scale(scale);

	set_collider(collider);
}

void Interactor::OnCollisionEnter(Collider* collider)
{
	if (collider->get_owner() ) {
		Interactor* interactee = reinterpret_cast<Interactor*>(collider->get_owner());
		if (interactee) {
			interactors_.push_back(interactee);
		}
	}
}

void Interactor::OnCollisionExit(Collider* collider)
{
	if (collider->get_owner()) {
		Interactor* interactee = reinterpret_cast<Interactor*>(collider->get_owner());
		if (interactee) {
			interactors_.erase(std::remove(interactors_.begin(), interactors_.end(), interactee), interactors_.end());
		}
	}
}



void Interactor::Update()
{
	set_pos(owner_->get_pos() + pos_offset_);
}

void Interactor::Render(ID3D11Device* p_d3d_device)
{

	Vector2 render_pos = WorldToRenderPos(get_pos());

#ifdef _DEBUG

	DrawRectangle(p_d3d_device, render_pos - get_collider()->get_scale() / 2.f, get_collider()->get_scale(), ARGB(0xFF00FFFF)); //³ë¶õ»ö
#endif
}
