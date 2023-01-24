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
	//타깃이 있을 때: 타깃 따라감
	if (look_target_ != nullptr) {
		move = look_target_->get_pos() - look_pos_;
	}
	//목적지가 지정되었을 때: 해당 목적지로 천천히 이동 
	else if(remain_second_>0){
		//Vector2 diff = look_pos_dest_ - look_pos_;
		//// 1초에 가야하는 거리*DtF() = 1프레임에 가야하는 거리
		//// = 남은 거리/시간 * DtF()
		//look_pos_ += (diff / remain_second_) * DtF();

		remain_second_ -= DtF();
	}
	//아무 상태도 아닐 때: WASD로 이동
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

	//카메라는 left_top + resolution/2.f 이하로 이동 불가.
	//			bottom_right - resolution/2.f 이상으로 이동 불가.
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

	
	
	
	//클릭한 곳으로 이동
	/*if (KEY_DOWN(KEY::LBUTTON) && MOUSE_IN_WINDOW()) {
		MoveTo(GET_MOUSE_POS(), .5f);
	}*/
	
	
}

Vector2 Camera::GetRenderPos(Vector2 world_pos)
{
	//카메라 원점(== 해상도/2 지점)
	Vector2 center_pos = Core::GetInstance()->get_resolution() / 2;
	//원점에서 카메라가 얼마나 이동했는가
	Vector2 diff = look_pos_ - center_pos;
	//카메라 이동량만큼 빼줌.
	return Vector2{ world_pos - diff};
}

Vector2 Camera::GetWorldPos(Vector2 render_pos)
{
	//카메라 원점(== 해상도/2 지점)
	Vector2 center_pos = Core::GetInstance()->get_resolution() / 2;
	//원점에서 얼마나 이동했는가
	Vector2 diff = look_pos_ - center_pos;
	//카메라 이동량만큼 더해줌.
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
