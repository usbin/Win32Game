#include "ItemAnimator.h"
#include "IItem.h"
#include "ItemAnimation.h"
ItemAnimator::ItemAnimator()
{
}
ItemAnimator::~ItemAnimator()
{
}
void ItemAnimator::CreateAnimation(const tstring& name, Texture* texture, Vector2 base_pos, Vector2 img_size, Vector2 img_distance, Vector2 offset, float duration, int img_count, bool is_repeat)
{

	ItemAnimation* anim = DEBUG_NEW ItemAnimation();
	anim->Init(name, texture, base_pos, img_size, img_distance, offset, duration, img_count, is_repeat);
	anim->set_animator(this);
	anims_.insert(std::make_pair(name, anim));

}
