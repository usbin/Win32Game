#include "Animator.h"
#include "Animation.h"

Animator::Animator()
	: owner_(nullptr)
	, anims_{}
	, current_anim_(nullptr) {
}

Animator::Animator(const Animator& origin)
	: owner_(nullptr)
	, anims_(origin.anims_)
	, current_anim_(nullptr){
}

Animator::~Animator()
{
	//애니메이션들 삭제
	SafeDeleteMap<tstring, Animation*>(anims_);
}

void Animator::CreateAnimation(
	const tstring& name, Texture* texture, Vector2 base_pos, Vector2 img_size, Vector2 img_distance, Vector2 offset
	, float duration, int img_count, bool is_repeat)
{
	Animation* anim = new Animation();
	anim->Init(name, texture, base_pos, img_size, img_distance, offset, duration, img_count, is_repeat);
	anim->set_animator(this);
	anims_.insert(std::make_pair(name, anim));
}

void Animator::Play(const tstring& name)
{
	Animation* anim = FindAnimation(name);
	current_anim_ = anim;
}

Animation* Animator::FindAnimation(const tstring& name)
{
	std::map<tstring, Animation*>::iterator iter = anims_.find(name);
	
	if (iter == anims_.end()) return nullptr;
	return iter->second;
}

void Animator::Update()
{
	if (current_anim_ == nullptr) return;
	if (current_anim_->is_repeat() && current_anim_->is_finished()) {
		current_anim_->ResetFrame();
	}
	current_anim_->Update();
}

void Animator::Render(HDC hdc)
{
	if (current_anim_ == nullptr) return;
	current_anim_->Render(hdc);
}
