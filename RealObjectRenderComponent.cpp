#include "RealObjectRenderComponent.h"
#include "RealObject.h"
#include "RealObjectSprite.h"
#include "RealObjectAnimator.h"
#include "Collider.h"

RealObjectRenderComponent::~RealObjectRenderComponent()
{

	delete sprite_;
	delete animator_;


}

void RealObjectRenderComponent::Update(GObject* owner)
{

	if (animator_ != nullptr) animator_->Update();
}
void RealObjectRenderComponent::Render(GObject* owner, ID3D11Device* p_d3d_device)
{
	RealObject* obj = dynamic_cast<RealObject*>(owner);
	owner_ = obj;
	if (obj) {
		if (!animator_ || animator_->is_finished()) {
			if (sprite_) {
				Vector2 pos = WorldToRenderPos(obj->get_pos());
				Vector2 scale = obj->get_scale();
				DrawTexture(p_d3d_device, pos - scale / 2.f, scale, sprite_->get_base_pos(), sprite_->get_scale(), sprite_->get_texture());
			}

		}
		else {
			animator_->Render(p_d3d_device);
		}
	}
	
}

void RealObjectRenderComponent::ChangeSprite(Sprite* sprite)
{
	if (sprite_) delete sprite_;
	sprite_ = dynamic_cast<RealObjectSprite*>(sprite);

}
