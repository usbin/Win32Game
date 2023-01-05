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
	virtual ~PlayerRenderComponent();

private:
	RealObject* owner_ = nullptr;
	RealObjectSprite* sprite_ = nullptr;
	RealObjectAnimator* animator_ = nullptr;
	RealObjectSprite* sprites[(int)DIRECTION::END][(int)PLAYER_STATE::END][(int)PLAYER_HAND_STATE::END] = { 0 };
	tstring state_animation_names[(int)DIRECTION::END][(int)PLAYER_STATE::END][(int)PLAYER_HAND_STATE::END] = { _T("") };
	tstring item_use_animation_names[(int)DIRECTION::END][(int)ITEM_CODE::END];

public:
	virtual void CreateAnimator();
	virtual void Update(GObject* owner);
	virtual void Render(GObject* owner, ID3D11Device* p_d3d_device);


	virtual GObjectSprite* get_sprite() { return sprite_; };
	virtual void ChangeSprite(GObjectSprite* sprite);
	inline void set_animator(RealObjectAnimator* animator) { animator_ = animator; };
	inline RealObjectAnimator* get_animator() { return animator_; };
	RealObject* get_owner() { return owner_; };

	
	virtual bool is_current_playing(tstring anim_name) override;
	virtual void PlayItemAnimation(ITEM_CODE item_code) override;

};

