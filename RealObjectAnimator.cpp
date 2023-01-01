#include "RealObjectAnimator.h"
#include "RealObjectAnimation.h"

RealObjectAnimator::RealObjectAnimator()
{
}

RealObjectAnimator::RealObjectAnimator(const RealObjectAnimator& origin)
	: Animator(origin)
{

}

RealObjectAnimator::~RealObjectAnimator()
{
}

void RealObjectAnimator::CreateAnimation(const tstring& name, Texture* texture, Vector2 base_pos, Vector2 img_size, Vector2 img_distance, Vector2 offset, float duration, int img_count, bool is_repeat)
{
	Animation* anim = new RealObjectAnimation();
	anim->Init(name, texture, base_pos, img_size, img_distance, offset, duration, img_count, is_repeat);
	anim->set_animator(this);
	anims_.insert(std::make_pair(name, anim));
}


