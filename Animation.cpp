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

	//������ ����
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

	//duration��ŭ �귶���� ���� ���������� �ѱ�
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

void Animation::Render(HDC hdc)
{

	//���� ������ �׸���
	const Vector2& pos = GetRenderPos(animator_->get_owner()->get_pos() + offset_);
		
	const AnimationFrame& frame = frames_[frame_index_];
	TransparentBlt(
		hdc														//������ dc
		, static_cast<int>(pos.x - frame.img_size.x / 2.)		//left ��ǥ
		, static_cast<int>(pos.y - frame.img_size.y / 2.)		//top ��ǥ
		, static_cast<int>(frame.img_size.x)					//���� ����
		, static_cast<int>(frame.img_size.y)					//���� ��ǥ
		, texture_->get_hdc()					//�ҽ� dc(=��Ʈ���� ���õ� �޸�dc)
		, static_cast<int>(frame.base_pos.x)	//��Ʈ���� left ��ǥ
		, static_cast<int>(frame.base_pos.y)	//��Ʈ���� top ��ǥ
		, static_cast<int>(frame.img_size.x)	//��Ʈ���� ���� ����
		, static_cast<int>(frame.img_size.y)	//��Ʈ���� ���� ����
		, RGB(255, 0, 255));					//������ �ȼ� ����

}

void Animation::ResetFrame()
{
	frame_index_ = 0;
	is_finished_ = false;
}