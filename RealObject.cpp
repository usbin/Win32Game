#include "RealObject.h"
#include "Collider.h"
#include "RealObjectAnimator.h"
#include "Sprite.h"
#include "Texture.h"
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
}


void RealObject::CreateCollider()
{
}

void RealObject::CreateAnimator()
{
}

void RealObject::CreateInteractor()
{
}

void RealObject::Render(ID3D11Device* p_d3d_device)
{
	if (get_visible()) {
		Sprite* sprite = get_sprite();
		const Vector2& pos = WorldToRenderPos(get_pos());
		const Vector2& scale = get_scale();
		if (sprite != nullptr) {
			Texture* texture = sprite->get_texture();
			const Vector2& sprite_base_pos = sprite->get_base_pos();
			const Vector2& sprite_scale = sprite->get_scale();
			DrawTexture(p_d3d_device, pos, scale, sprite_base_pos, sprite_scale, texture);
		}
	}
	
}

void RealObject::FinalUpdate() {
	// 컴포넌트들에 대한 FinalUpdate들 모음.
	if (collider_ != nullptr) collider_->FinalUpdate();
	
	if (animator_ != nullptr) animator_->Update();
	


}
void RealObject::ComponentRender(ID3D11Device* p_d3d_device)
{
	// 컴포넌트들에 대한 렌더링
	if (collider_ != nullptr) collider_->Render(p_d3d_device);
	if (animator_ != nullptr) animator_->Render(p_d3d_device);
}

void RealObject::SaveToFile(FILE* p_file)
{
	GObject::SaveToFile(p_file);

	fwrite(&collider_, sizeof(DWORD_PTR), 1, p_file);
	if (collider_) collider_->SaveToFile(p_file);

	fwrite(&animator_, sizeof(DWORD_PTR), 1, p_file);
	if (animator_) animator_->SaveToFile(p_file);

}
void RealObject::LoadFromFile(FILE* p_file)
{
	GObject::LoadFromFile(p_file);

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
