#include "RealObject.h"
#include "Collider.h"
#include "RealObjectAnimator.h"
#include "Texture.h"
#include "IControlComponent.h"
#include "PhysicsComponent.h"
#include "Animator.h"
#include "Animation.h"
#include "UiSprite.h"
#include "RealObjectSprite.h"
#include "Interactor.h"
#include "IItemHolder.h"

RealObject::RealObject()
	: GObject()
	, collider_(nullptr)
	, control_cmp_(nullptr)
	, physics_cmp_(nullptr)
	, render_cmp_(nullptr)
	, interactor_(nullptr)
{
}




RealObject::~RealObject() {

	delete collider_;
	delete control_cmp_;
	delete physics_cmp_;
	delete render_cmp_;
	delete item_holder_;
}


void RealObject::Render(ID3D11Device* p_d3d_device)
{
	if (get_visible()) {
		// animator�� ���ų� �������� �ƴ� ���� �׸���

		if (render_cmp_) render_cmp_->Render(this, p_d3d_device);
	}
	
}

void RealObject::FinalUpdate() {
	// ������Ʈ�鿡 ���� FinalUpdate�� ����.
	if (collider_ != nullptr) collider_->FinalUpdate();
	if (control_cmp_ != nullptr) control_cmp_->Update(this);
	if (physics_cmp_ != nullptr) physics_cmp_->FinalUpdate(this);
	if (render_cmp_ != nullptr) render_cmp_->Update(this);
	if (item_holder_) item_holder_->Update();


}
void RealObject::ComponentRender(ID3D11Device* p_d3d_device)
{
	// ������Ʈ�鿡 ���� ������
	if (collider_ != nullptr) collider_->Render(p_d3d_device);
	if (item_holder_) item_holder_->Render(p_d3d_device);
}

