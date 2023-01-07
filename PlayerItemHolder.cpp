#include "PlayerItemHolder.h"
#include "IItem.h"
#include "Player.h"
#include "ItemSprite.h"
PlayerItemHolder::PlayerItemHolder()
{
	holder_scale_ = Vector2{ 96, 96 };
}

PlayerItemHolder::~PlayerItemHolder()
{
}

void PlayerItemHolder::Update()
{
	if (item_ && owner_) {
		item_->UpdateOnHolder(this);
	}
}

void PlayerItemHolder::Render(ID3D11Device* p_d3d_device)
{
	if (item_ && owner_) {
		item_->RenderOnHolder(this, p_d3d_device);
	}
}

void PlayerItemHolder::SetItem(const IItem* item)
{
	item_ = item;
	if (owner_) {
		if (item_) {
			owner_->OnHold(item);
			item_->OnHold(owner_);
		}
		else owner_->OnUnhold();
	}
}
