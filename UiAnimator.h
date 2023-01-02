#pragma once
#include "Animator.h"
class UiAnimator : public Animator
{
	// Animator을(를) 통해 상속됨
	virtual void CreateAnimation(const tstring& name, Texture* texture, Vector2 base_pos, Vector2 img_size, Vector2 img_distance, Vector2 offset, float duration, int img_count, bool is_repeat) override;

};

