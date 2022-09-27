#include "RealObject.h"
#include "Collider.h"
#include "Animator.h"

RealObject::RealObject()
	: GObject()
{
}

RealObject::RealObject(const RealObject& origin)
	: GObject(origin)
	, direction_(DIRECTION::DOWN)
	, collider_(nullptr)
	, animator_(nullptr)

{

	if (origin.collider_ != nullptr) {

		collider_ = new Collider(*(origin.collider_));
		collider_->set_owner(this);
	}
	if (origin.animator_ != nullptr) {
		animator_ = new Animator(*(origin.animator_));
		animator_->set_owner(this);
	}
}




RealObject::~RealObject() {

	delete collider_;
	delete animator_;
}


void RealObject::FinalUpdate() {
	// ������Ʈ�鿡 ���� FinalUpdate�� ����.
	if (collider_ != nullptr) collider_->FinalUpdate();
	if (animator_ != nullptr) animator_->Update();


}
void RealObject::ComponentRender(HDC hdc)
{
	// ������Ʈ�鿡 ���� ������
	if (collider_ != nullptr) collider_->Render(hdc);
	if (animator_ != nullptr) animator_->Render(hdc);
}