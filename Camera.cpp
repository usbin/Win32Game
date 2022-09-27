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
	//Ÿ���� ���� ��: Ÿ�� ����
	if (look_target_ != nullptr) {
		look_pos_ = look_target_->get_pos();
	}
	//�������� �����Ǿ��� ��: �ش� �������� õõ�� �̵� 
	else if(remain_second_>0){
		//Vector2 diff = look_pos_dest_ - look_pos_;
		//// 1�ʿ� �����ϴ� �Ÿ�*DtF() = 1�����ӿ� �����ϴ� �Ÿ�
		//// = ���� �Ÿ�/�ð� * DtF()
		//look_pos_ += (diff / remain_second_) * DtF();

		//remain_second_ -= DtF();
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
		look_pos_ += direction.Normalize() * DtF() * 200.f;

		
	}
	if (KEY_DOWN(KEY::LBUTTON) && MOUSE_IN_WINDOW()) {
		MoveTo(GET_MOUSE_POS(), .5f);
	}
	
	
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
