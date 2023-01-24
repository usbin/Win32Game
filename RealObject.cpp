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
#include "PlayerRenderComponent.h"

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
		// animator가 없거나 실행중이 아닐 때만 그리기

		if (render_cmp_) render_cmp_->Render(this, p_d3d_device);
	}
	
}

void RealObject::FinalUpdate() {
	// 컴포넌트들에 대한 FinalUpdate들 모음.
	if (collider_ != nullptr) collider_->FinalUpdate();
	if (control_cmp_ != nullptr) control_cmp_->Update(this);
	if (physics_cmp_ != nullptr) physics_cmp_->FinalUpdate(this);
	if (render_cmp_ != nullptr) render_cmp_->Update(this);
	if (item_holder_) item_holder_->Update();


}
void RealObject::ComponentRender(ID3D11Device* p_d3d_device)
{
	// 컴포넌트들에 대한 렌더링
	if (collider_ != nullptr) collider_->Render(p_d3d_device);
	if (item_holder_) item_holder_->Render(p_d3d_device);
}

void RealObject::MoveTo(GObject* gobject)
{
	GObject::MoveTo(gobject);

	RealObject* real_object = dynamic_cast<RealObject*>(gobject);
	if (real_object) {
		delete real_object->collider_;
		collider_->set_owner(real_object);
		real_object->set_collider(collider_);
		set_collider(nullptr);
		
		//interactor는 GObject라 씬에 종속적. 따라서 자동 생성되는 거 그대로 사용.
		

		delete real_object->control_cmp_;
		real_object->set_control_component(control_cmp_);
		set_control_component(nullptr);

		delete real_object->physics_cmp_;
		real_object->set_physics_component(physics_cmp_);
		set_physics_component(nullptr);

		delete real_object->render_cmp_;
		real_object->set_render_component(render_cmp_);
		set_render_component(nullptr);

		real_object->set_velocity(Vector2::Zero());

		delete real_object->item_holder_;
		item_holder_->set_owner(real_object);
		real_object->item_holder_ = item_holder_;
		item_holder_ = nullptr;

	}
}
