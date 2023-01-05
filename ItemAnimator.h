#pragma once
#include "global.h"
#include "Animator.h"
class GObject;
class IItemHolder;
class ItemAnimator : public Animator
{
public:
	ItemAnimator();
	virtual ~ItemAnimator();
private:
	IItemHolder* holder_ = nullptr;

public:
	IItemHolder* get_owner() { return holder_; };
	void set_owner(IItemHolder* owner) { holder_ = owner; };

	// Animator을(를) 통해 상속됨
	virtual void CreateAnimation(const tstring& name, Texture* texture, Vector2 base_pos, Vector2 img_size, Vector2 img_distance, Vector2 offset, float duration, int img_count, bool is_repeat) override;
};

