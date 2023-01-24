#include "Camera.h"
#include "GObject.h"
#include "Core.h"
Camera::Camera()
	: look_target_(nullptr)
	, look_pos_(Core::GetInstance()->get_resolution() / 2)
	, remain_second_(0.){

}
Camera::~Camera() {

}
void Camera::Update()
{
	Vector2 move;
	//Ÿ���� ���� ��: Ÿ�� ����
	if (look_target_ != nullptr) {
		move = look_target_->get_pos() - look_pos_;
	}
	//�������� �����Ǿ��� ��: �ش� �������� õõ�� �̵� 
	else if(remain_second_>0){
		//Vector2 diff = look_pos_dest_ - look_pos_;
		//// 1�ʿ� �����ϴ� �Ÿ�*DtF() = 1�����ӿ� �����ϴ� �Ÿ�
		//// = ���� �Ÿ�/�ð� * DtF()
		//look_pos_ += (diff / remain_second_) * DtF();

		remain_second_ -= DtF();
	}
	//�ƹ� ���µ� �ƴ� ��: WASD�� �̵�
	else {
		Vector2 direction{};
		if (KEY_HOLD(KEY::A)) {
			direction.x = -1;
		}
		else if (KEY_HOLD(KEY::D)) {
			direction.x = 1;
		}
		if (KEY_HOLD(KEY::W)) {
			direction.y = -1;
		}
		else if (KEY_HOLD(KEY::S)) {
			direction.y = 1;
		}
		move = direction.Normalize() * DtF() * 800.f;

		
	}

	//ī�޶�� left_top + resolution/2.f ���Ϸ� �̵� �Ұ�.
	//			bottom_right - resolution/2.f �̻����� �̵� �Ұ�.
	if (is_limited_) {
		if ((look_pos_.x + move.x < left_top_limit.x + Core::GetInstance()->get_resolution().x / 2.f)
			&& move.x < 0) {
			move.x = 0;
		}
		if ((look_pos_.x + move.x > bottom_right_limit.x - Core::GetInstance()->get_resolution().x / 2.f)
			&& move.x > 0) {
			move.x = 0;
		}
		if ((look_pos_.y + move.y < left_top_limit.y + Core::GetInstance()->get_resolution().y / 2.f)
			&& move.y < 0) {
			move.y = 0;
		}
		if((look_pos_.y + move.y > bottom_right_limit.y - Core::GetInstance()->get_resolution().y / 2.f)
			&& move.y > 0) {
			move.y = 0;
		}
	}
	

	look_pos_ += move;

	
	
	
	//Ŭ���� ������ �̵�
	/*if (KEY_DOWN(KEY::LBUTTON) && MOUSE_IN_WINDOW()) {
		MoveTo(GET_MOUSE_POS(), .5f);
	}*/
	
	
}

Vector2 Camera::GetRenderPos(Vector2 world_pos)
{
	//ī�޶� ����(== �ػ�/2 ����)
	Vector2 center_pos = Core::GetInstance()->get_resolution() / 2;
	//�������� ī�޶� �󸶳� �̵��ߴ°�
	Vector2 diff = look_pos_ - center_pos;
	//ī�޶� �̵�����ŭ ����.
	return Vector2{ world_pos - diff};
}

Vector2 Camera::GetWorldPos(Vector2 render_pos)
{
	//ī�޶� ����(== �ػ�/2 ����)
	Vector2 center_pos = Core::GetInstance()->get_resolution() / 2;
	//�������� �󸶳� �̵��ߴ°�
	Vector2 diff = look_pos_ - center_pos;
	//ī�޶� �̵�����ŭ ������.
	return Vector2{ render_pos + diff};
}

void Camera::MoveTo(Vector2 dest, float second)
{
	look_pos_dest_ = dest;
	remain_second_ = second;
}

void Camera::set_limit(Vector2 left_top, Vector2 bottom_right)
{
	left_top_limit = left_top;
	bottom_right_limit = bottom_right;
	is_limited_ = true;
}
