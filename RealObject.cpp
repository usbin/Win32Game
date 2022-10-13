#include "RealObject.h"
#include "Collider.h"
#include "Animator.h"
#include "Sprite.h"
#include "Texture.h"
RealObject::RealObject()
	: GObject()
	, animator_(nullptr)
	, collider_(nullptr)
	, direction_(DIRECTION::DOWN)
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


void RealObject::CreateCollider()
{
}

void RealObject::CreateAnimator()
{
}

void RealObject::Render(HDC hdc)
{
	Sprite* sprite = get_sprite();
	const Vector2& pos = WorldToRenderPos(get_pos());
	const Vector2& scale = get_scale();
	if (sprite != nullptr) {
		Texture* texture = sprite->get_texture();
		const Vector2& sprite_base_pos = sprite->get_base_pos();
		const Vector2& sprite_scale = sprite->get_scale();
		TransparentBlt(hdc
			, static_cast<int>(pos.x-scale.x/2.f)
			, static_cast<int>(pos.y-scale.y/2.f)
			, static_cast<int>(scale.x)
			, static_cast<int>(scale.y)
			, texture->get_hdc()
			, static_cast<int>(sprite_base_pos.x)
			, static_cast<int>(sprite_base_pos.y)
			, static_cast<int>(sprite_scale.x					   )
			, static_cast<int>(sprite_scale.y					   )
			, RGB(255, 0, 255));
	}
}

void RealObject::FinalUpdate() {
	// 컴포넌트들에 대한 FinalUpdate들 모음.
	if (collider_ != nullptr) collider_->FinalUpdate();
	
	if (animator_ != nullptr) animator_->Update();
	


}
void RealObject::ComponentRender(HDC hdc)
{
	// 컴포넌트들에 대한 렌더링
	if (collider_ != nullptr) collider_->Render(hdc);
	if (animator_ != nullptr) animator_->Render(hdc);
}