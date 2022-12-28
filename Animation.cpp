#include "Animation.h"
#include "Animator.h"
#include "GObject.h"
#include "Texture.h"
#include "Camera.h"

Animation::Animation()
	: name_(_T(""))
	, texture_(nullptr)
	, offset_(Vector2{ 0, 0 })
	, duration_(0.)
	, is_repeat_(false)
	, animator_(nullptr)
	, frame_index_(0)
	, frame_acc_dt_(0.)
	, img_count_(0)
	, is_finished_(false)
{
}

Animation::~Animation()
{
}

void Animation::Init(tstring name, Texture* texture, Vector2 base_pos, Vector2 img_size, Vector2 img_distance
	, Vector2 offset, float duration, int img_count, bool is_repeat)
{
	name_ = name;
	texture_ = texture;
	duration_ = duration;
	is_repeat_ = is_repeat;
	img_count_ = img_count;
	offset_ = offset;

	//프레임 생성
	for (int i = 0; i < img_count; i++) {
		AnimationFrame frame{};
		frame.base_pos = base_pos + (img_distance)*i;
		frame.img_size = img_size;
		frames_.push_back(frame);
	}
}

void Animation::Update()
{
	if (is_finished_) return;

	//duration만큼 흘렀으면 다음 프레임으로 넘김
	frame_acc_dt_ += DtF();
	if (frame_acc_dt_ >= duration_) {
		if (++frame_index_ >= img_count_) {
			is_finished_ = true;
			frame_index_ = 0;
			return;
		}
		frame_acc_dt_ -= duration_;
	}
}


void Animation::ResetFrame()
{
	frame_index_ = 0;
	is_finished_ = false;
}

void Animation::SaveToFile(FILE* p_file)
{
	//1. name 길이 저장
	//2. name 저장
	//2. texture 저장
	//3. duration 저장
	//4. is_repeat 저장
	//5. img_count 저장
	//6. offset 저장
	//7. is_finished 저장
	//8. frames 저장
	UINT name_size = name_.size() + 1;
	const TCHAR* name_cstr = name_.c_str();
	fwrite(&name_size, sizeof(UINT), 1, p_file);
	fwrite(name_cstr, sizeof(TCHAR), name_size, p_file);
	texture_->SaveToFile(p_file);
	fwrite(&duration_, sizeof(float), 1, p_file);
	fwrite(&is_repeat_, sizeof(bool), 1, p_file);
	fwrite(&img_count_, sizeof(int), 1, p_file);
	fwrite(&offset_, sizeof(Vector2), 1, p_file);
	fwrite(&is_finished_, sizeof(bool), 1, p_file);
	UINT frame_size = frames_.size();
	fwrite(&frame_size, sizeof(UINT), 1, p_file);
	for (AnimationFrame frame : frames_) {
		fwrite(&frame, sizeof(AnimationFrame), 1, p_file);
	}

}

void Animation::LoadFromFile(FILE* p_file)
{
	//1. name 길이 로드
	//2. name 로드
	//2. texture 로드
	//3. duration 로드
	//4. is_repeat 로드
	//5. img_count 로드
	//6. offset 로드
	//7. is_finished 로드
	//8. frames 로드
	UINT name_size = 0;
	fread(&name_size, sizeof(UINT), 1, p_file);
	TCHAR* name_cstr = new TCHAR[name_size];
	fread(name_cstr, sizeof(TCHAR), name_size, p_file);
	name_ = name_cstr;
	delete[] name_cstr;

	Res* texture_res = new Res();
	texture_res->LoadFromFile(p_file);
	texture_ = ResManager::GetInstance()->LoadTexture(texture_res->get_key(), texture_res->get_relative_path());
	delete texture_res;
	fread(&duration_, sizeof(float), 1, p_file);
	fread(&is_repeat_, sizeof(bool), 1, p_file);
	fread(&img_count_, sizeof(int), 1, p_file);
	fread(&offset_, sizeof(Vector2), 1, p_file);
	fread(&is_finished_, sizeof(bool), 1, p_file);
	UINT frame_size = frames_.size();
	fread(&frame_size, sizeof(UINT), 1, p_file);
	for (int i = 0; i < frame_size; i++) {
		AnimationFrame frame{};
		fread(&frame, sizeof(AnimationFrame), 1, p_file);
		frames_.push_back(frame);
	}
}
