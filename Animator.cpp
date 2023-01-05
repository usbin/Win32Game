#include "Animator.h"
#include "Animation.h"
#include "RealObjectAnimation.h"
#include "UiAnimation.h"

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

void Animator::Play(const tstring& name, bool exclusive)
{
	if (!exclusive_ || is_finished()) {
		Animation* anim = FindAnimation(name);
		if (anim) {
			current_anim_ = anim;
			current_anim_->ResetFrame();
			exclusive_ = exclusive;
		}
	}
	
}

void Animator::Stop()
{
	if(!exclusive_)
		current_anim_ = nullptr;
}

Animation* Animator::FindAnimation(const tstring& name)
{
	std::map<tstring, Animation*>::iterator iter = anims_.find(name);
	
	if (iter == anims_.end()) return nullptr;
	return iter->second;
}

bool Animator::is_current_playing(const tstring& name)
{
	auto it = anims_.find(name);
	if (it == anims_.end()) return false;
	return (!is_finished()) && it->second == current_anim_;
}

void Animator::Update()
{
	if (current_anim_ == nullptr) return;
	if (current_anim_->is_repeat() && current_anim_->is_finished()) {
		current_anim_->ResetFrame();
	}
	current_anim_->Update();
}

void Animator::Render(ID3D11Device* p_d3d_device)
{
	if (current_anim_ == nullptr) return;
	current_anim_->Render(p_d3d_device);
}
