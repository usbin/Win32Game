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


void RealObjectAnimator::SaveToFile(FILE* p_file)
{
	//1.전체 애니메이션 개수 저장
	UINT anims_size = anims_.size();
	fwrite(&anims_size, sizeof(UINT), 1, p_file);
	for (std::pair<const tstring, Animation*> pair : anims_) {
		//2.tstring 길이 저장
		//3.tstring 저장
		//4.Animation 저장
		UINT size = pair.first.size() + 1;
		const TCHAR* anim_key_cstr = pair.first.c_str();
		fwrite(&size, sizeof(UINT), 1, p_file);
		fwrite(anim_key_cstr, sizeof(TCHAR), size, p_file);
		pair.second->SaveToFile(p_file);
	}
}

void RealObjectAnimator::LoadFromFile(FILE* p_file)
{
	//1.전체 애니메이션 개수 로드
	UINT anims_size = 0;
	fread(&anims_size, sizeof(UINT), 1, p_file);
	for (int i = 0; i < anims_size; i++) {
		//2.tstring 길이 로드
		//3.tstring 로드
		//4.Animation 로드
		//5.current animation는 첫번째 항목으로 설정
		UINT size = 0;
		fread(&size, sizeof(UINT), 1, p_file);
		TCHAR* anim_key_cstr = new TCHAR[size];
		fread(anim_key_cstr, sizeof(TCHAR), size, p_file);
		tstring anim_key = anim_key_cstr;
		delete[] anim_key_cstr;
		Animation* anim = new RealObjectAnimation();
		anim->LoadFromFile(p_file);
		anim->set_animator(this);
		anims_.insert(std::make_pair(anim_key, anim));
		current_anim_ = anims_.begin()->second;
	}
}
