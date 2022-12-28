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

void Animator::Render(ID3D11Device* p_d3d_device)
{
	if (current_anim_ == nullptr) return;
	current_anim_->Render(p_d3d_device);
}

void Animator::SaveToFile(FILE* p_file)
{
}

void Animator::LoadFromFile(FILE* p_file)
{
}

