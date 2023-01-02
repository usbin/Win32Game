#pragma once
#include "global.h"
class IRenderComponent
{
public:
	virtual ~IRenderComponent() = 0 {};
	virtual void Update(GObject* owner)=0;
	virtual void Render(GObject* owner, ID3D11Device* p_d3d_device) =0;
	virtual Sprite* get_sprite() = 0;
	virtual void ChangeSprite(Sprite* sprite) = 0;
};

