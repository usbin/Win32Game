#include "RealObject.h"
#include "Collider.h"
#include "RealObjectAnimator.h"
#include "Sprite.h"
#include "Texture.h"
#include "ControlComponent.h"
#include "PhysicsComponent.h"
#include "Animator.h"
#include "Animation.h"
#include "UiSprite.h"
#include "RealObjectSprite.h"

RealObject::RealObject()
	: GObject()
	, animator_(nullptr)
	, collider_(nullptr)
{
}

RealObject::RealObject(const RealObject& origin)
	: GObject(origin)
	, collider_(nullptr)
	, animator_(nullptr)

{

	if (origin.collider_ != nullptr) {

		collider_ = new Collider(*(origin.collider_));
		collider_->set_owner(this);
	}
	if (origin.animator_ != nullptr) {
		animator_ = new RealObjectAnimator(*(dynamic_cast<RealObjectAnimator*>(origin.animator_)));
		animator_->set_owner(this);
	}
}




RealObject::~RealObject() {

	delete collider_;
	delete animator_;
	delete control_cmp_;
	delete physics_cmp_;
	delete render_cmp_;
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
	if (animator_ != nullptr) animator_->Update();
	if (control_cmp_ != nullptr) control_cmp_->Update(this);
	if (physics_cmp_ != nullptr) physics_cmp_->FinalUpdate(this);
	if (render_cmp_ != nullptr) render_cmp_->Update(this);


}
void RealObject::ComponentRender(ID3D11Device* p_d3d_device)
{
	// 컴포넌트들에 대한 렌더링
	if (collider_ != nullptr) collider_->Render(p_d3d_device);
}

void RealObject::SaveToFile(FILE* p_file)
{
	GObject::SaveToFile(p_file);


	fwrite(&render_cmp_, sizeof(DWORD_PTR), 1, p_file);
	if (render_cmp_) render_cmp_->SaveToFile(p_file);

	fwrite(&collider_, sizeof(DWORD_PTR), 1, p_file);
	if (collider_) collider_->SaveToFile(p_file);

	fwrite(&animator_, sizeof(DWORD_PTR), 1, p_file);
	if (animator_) animator_->SaveToFile(p_file);

}
void RealObject::LoadFromFile(FILE* p_file)
{
	GObject::LoadFromFile(p_file);

	if (render_cmp_) delete render_cmp_;
	if (collider_) delete collider_;
	if (animator_) delete animator_;

	fread(&render_cmp_, sizeof(DWORD_PTR), 1, p_file);
	if (render_cmp_) {
		render_cmp_ = new RealObjectRenderComponent(this);
		render_cmp_->LoadFromFile(p_file);
	}


	fread(&collider_, sizeof(DWORD_PTR), 1, p_file);
	if (collider_) {
		collider_ = new Collider();
		collider_->LoadFromFile(p_file);
		collider_->set_owner(this);

	}

	fread(&animator_, sizeof(DWORD_PTR), 1, p_file);
	if (animator_) {
		animator_ = new RealObjectAnimator();
		animator_->LoadFromFile(p_file);
		animator_->set_owner(this);
	}


}
