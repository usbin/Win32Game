#pragma once
#include "global.h"
#include "IRenderComponent.h"
#include "RealObjectSprite.h"
class GObject;
class GObjectSprite;
class RealObjectAnimator;
class RealObject;
class RealObjectSprite;

class RealObjectRenderComponent : public IRenderComponent
{
public:
	RealObjectRenderComponent(RealObject* owner);
	virtual ~RealObjectRenderComponent();

private:
	RealObject* owner_ = nullptr;
	RealObjectSprite* sprite_ = nullptr;
	RealObjectAnimator* animator_ = nullptr;
	RENDER_LAYER render_layer_ = RENDER_LAYER::GROUND;

public:
	virtual void Update(GObject* owner);
	virtual void Render(GObject* owner, ID3D11Device* p_d3d_device);

	virtual ISprite* get_sprite() { return static_cast<ISprite*>(sprite_); };
	virtual void ChangeSprite(ISprite* sprite);
	inline void set_animator(RealObjectAnimator* animator) { animator_ = animator; };
	inline RealObjectAnimator* get_animator() { return animator_; };
	RealObject* get_owner() { return owner_; };
	inline void set_render_layer(RENDER_LAYER layer) { render_layer_ = layer; };

	virtual bool is_current_playing(tstring anim_name) override;
	virtual void PlayItemAnimation(ITEM_CODE item_code) override;

};

