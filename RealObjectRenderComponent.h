#pragma once
#include "global.h"
#include "IRenderComponent.h"
#include "RealObjectSprite.h"
class GObject;
class Sprite;
class RealObjectAnimator;
class RealObject;
class RealObjectSprite;

class RealObjectRenderComponent : public IRenderComponent
{
public:
	RealObjectRenderComponent(GObject* owner) {};
	virtual ~RealObjectRenderComponent();

private:
	RealObject* owner_;
	RealObjectSprite* sprite_;
	RealObjectAnimator* animator_;

public:
	virtual void Update(GObject* owner);
	virtual void Render(GObject* owner, ID3D11Device* p_d3d_device);

	virtual Sprite* get_sprite() { return static_cast<Sprite*>(sprite_); };
	virtual void ChangeSprite(Sprite* sprite);
	inline void set_animator(RealObjectAnimator* animator) { animator_ = animator; };
	inline RealObjectAnimator* get_animator() { return animator_; };
	RealObject* get_owner() { return owner_; };

};

