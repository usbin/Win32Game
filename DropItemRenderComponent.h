#pragma once
#include "global.h"
#include "IRenderComponent.h"
class DropItem;
class DropItemRenderComponent : public IRenderComponent
{
private:
	DropItem* owner_ = nullptr;

public:
	DropItemRenderComponent(DropItem* owner);
	// IRenderComponent을(를) 통해 상속됨
	virtual void Update(GObject* owner) override;
	virtual void Render(GObject* owner, ID3D11Device* p_d3d_device) override;
	virtual void PlayItemAnimation(ITEM_CODE item_code) override;
	virtual bool is_current_playing(tstring anim_name) override;

	// IRenderComponent을(를) 통해 상속됨
	virtual ISprite* get_sprite() override;
	virtual void ChangeSprite(ISprite* sprite) override;
};

