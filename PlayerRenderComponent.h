#pragma once
#include "global.h"
#include "IRenderComponent.h"
class RealObject;
class RealObjectAnimator;
class RealObjectSprite;
class PlayerRenderComponent : public IRenderComponent
{
public:
	PlayerRenderComponent(GObject* owner);
	~PlayerRenderComponent();

private:
	RealObject* owner_;
	RealObjectSprite* sprite_;
	RealObjectAnimator* animator_;
	Sprite* sprites[(int)DIRECTION::END][(int)PLAYER_STATE::END];

public:
	virtual void CreateAnimator();
	virtual void Update(GObject* owner);
	virtual void Render(GObject* owner, ID3D11Device* p_d3d_device);


	virtual Sprite* get_sprite() { return sprite_; };
	virtual void ChangeSprite(Sprite* sprite);
	inline void set_animator(RealObjectAnimator* animator) { animator_ = animator; };
	inline RealObjectAnimator* get_animator() { return animator_; };
	RealObject* get_owner() { return owner_; };
};

