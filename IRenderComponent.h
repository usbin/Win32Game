#pragma once
#include "global.h"
class ISprite;
class IRenderComponent
{
public:
	virtual ~IRenderComponent() = 0 {};
	virtual void Update(GObject* owner)=0;
	virtual void Render(GObject* owner, ID3D11Device* p_d3d_device) =0;
	virtual ISprite* get_sprite() = 0;
	virtual void ChangeSprite(ISprite* sprite) = 0;
	virtual void PlayItemAnimation(ITEM_CODE item_code)=0;
	virtual bool is_current_playing(tstring anim_name)=0;
};

