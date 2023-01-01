#include "RealObjectRenderComponent.h"
#include "RealObject.h"
#include "Animator.h"
#include "RealObjectSprite.h"

void RealObjectRenderComponent::Render(GObject* owner, ID3D11Device* p_d3d_device)
{
	RealObject* obj = dynamic_cast<RealObject*>(owner);
	if (obj) {
		if (!obj->get_animator() || obj->get_animator()->is_finished()) {
			if (sprite_) {
				Vector2 pos = WorldToRenderPos(obj->get_pos());
				Vector2 scale = obj->get_scale();
				DrawTexture(p_d3d_device, pos - scale / 2.f, scale, sprite_->get_base_pos(), sprite_->get_scale(), sprite_->get_texture());
			}

		}
	}
	
}

void RealObjectRenderComponent::ChangeSprite(Sprite* sprite)
{
	if (sprite_) delete sprite_;
	sprite_ = sprite;

}

void RealObjectRenderComponent::SaveToFile(FILE* p_file)
{
	fwrite(&sprite_, sizeof(DWORD_PTR), 1, p_file);
	if (sprite_) {
		sprite_->SaveToFile(p_file);
	}
}

void RealObjectRenderComponent::LoadFromFile(FILE* p_file)
{

	fread(&sprite_, sizeof(DWORD_PTR), 1, p_file);
	if (sprite_) {
		sprite_ = new RealObjectSprite();
		sprite_->LoadFromFile(p_file);
	}

	
}
