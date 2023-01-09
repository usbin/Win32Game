#pragma once
#include "global.h"
#include "IRenderComponent.h"
class ITileObjectInfo;
class TileObject;
class TileObjectSprite;
class TileObjectRenderComponent : public IRenderComponent
{
private:
	
	ITileObjectInfo* tile_object_info_ = nullptr;
public:
	// IRenderComponent을(를) 통해 상속됨
	virtual void Update(GObject* owner) override;
	virtual void Render(GObject* owner, ID3D11Device* p_d3d_device) override;
	virtual void ChangeSprite(ISprite* sprite) override final {};
	virtual void PlayItemAnimation(ITEM_CODE item_code) override final {};
	virtual bool is_current_playing(tstring anim_name) override final { return false; };

	// IRenderComponent을(를) 통해 상속됨
	virtual ISprite* get_sprite() override;

};

