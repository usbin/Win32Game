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
	frame_acc_dt_ = 0;
	frame_index_ = 0;
	is_finished_ = false;
}
