#include "pch.h"
#include "GObject.h"
#include "Collider.h"
#include "Animator.h"

unsigned int GObject::id_counter_ = 1;
void GObject::CreateCollider()
{
}
void GObject::CreateAnimator()
{
}
GObject::GObject()
	: name_(_T(""))
	, pos_(Vector2{0,0})
	, scale_(Vector2{ 0,0 })
	, direction_(DIRECTION::DOWN)
	, id_(id_counter_++)
	, group_type_(GROUP_TYPE::DEFAULT)
	, collider_(nullptr)
	, animator_(nullptr)
	, is_dead_(false){

}
GObject::GObject(const GObject& origin)
	: name_(_T(""))
	, pos_(origin.pos_)
	, scale_(origin.scale_)
	, direction_(origin.direction_)
	, id_(id_counter_++)
	, group_type_(origin.group_type_)
	, collider_(nullptr)
	, animator_(nullptr)
	, is_dead_(false) {
	if (origin.collider_ != nullptr) {

		collider_ = new Collider(*(origin.collider_));
		collider_->set_owner(this);
	}
	if (origin.animator_ != nullptr) {
		animator_ = new Animator(*(origin.animator_));
		animator_->set_owner(this);
	}

}
GObject::~GObject(){
	delete collider_;
	delete animator_;
}



void GObject::FinalUpdate() {
	// 컴포넌트들에 대한 FinalUpdate들 모음.
	if (collider_ != nullptr) collider_->FinalUpdate();
	if (animator_ != nullptr) animator_->Update();
}

void GObject::ComponentRender(HDC hdc) {
	// 컴포넌트들에 대한 렌더링
	if (collider_ != nullptr) collider_->Render(hdc);
	if (animator_ != nullptr) animator_->Render(hdc);
}

void GObject::OnCollisionEnter(const Collider& collider)
{
}

void GObject::OnCollisionStay(const Collider& collider)
{
}

void GObject::OnCollisionExit(const Collider& collider)
{
}
