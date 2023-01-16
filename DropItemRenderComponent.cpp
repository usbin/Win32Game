#include "DropItemRenderComponent.h"

#include "DropItem.h"
#include "IItem.h"
#include "ItemSprite.h"
DropItemRenderComponent::DropItemRenderComponent(DropItem* owner)
{
	owner_ = owner;
}

void DropItemRenderComponent::Update(GObject* owner)
{
}

void DropItemRenderComponent::Render(GObject* owner, ID3D11Device* p_d3d_device)
{
	DropItem* _owner = dynamic_cast<DropItem*>(owner);
	if (_owner && _owner->get_item() && _owner->get_item()->get_sprite()) {
		ItemSprite* sprite = _owner->get_item()->get_sprite();
		DrawTexture(p_d3d_device, WorldToRenderPos(_owner->get_pos() - _owner->get_scale() / 2.f), _owner->get_scale()
			, sprite->get_base_pos(), sprite->get_scale(), sprite->get_texture());
	}
}
void DropItemRenderComponent::PlayItemAnimation(ITEM_CODE item_code)
{
}

bool DropItemRenderComponent::is_current_playing(tstring anim_name)
{
	return false;
}

ISprite* DropItemRenderComponent::get_sprite()
{
	DropItem* _owner = dynamic_cast<DropItem*>(owner_);
	return _owner->get_item()->get_sprite();
}

void DropItemRenderComponent::ChangeSprite(ISprite* sprite)
{
	//아이템의 sprite는 변경 불가.
	return;
}
