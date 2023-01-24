#pragma once
#include "global.h"
class GObject;

class Camera
{
	SINGLETON(Camera);

private:
	Vector2 look_pos_ = Vector2::Zero();		//카메라가 보는 위치(중심 좌표)
	GObject* look_target_ = nullptr;	//타깃이 있으면 따라감


	Vector2 look_pos_dest_ = Vector2::Zero();	//천천히 움직여서 도착할 위치
	float remain_second_ = 0;	//도착하기까지 몇 초 남았는지

	bool is_limited_ = false;
	Vector2 left_top_limit;
	Vector2 bottom_right_limit;

public:
	void Update();
	Vector2 GetRenderPos(Vector2 world_pos);	//카메라 기준 좌표
	Vector2 GetWorldPos(Vector2 render_pos);	//월드 좌표
	void MoveTo(Vector2 dest, float second);	//second에 걸쳐 dest에 도착
	void set_look_pos(Vector2 look_pos) { look_pos_ = look_pos; };
	Vector2 get_look_pos() { return look_pos_; };
	void set_target(GObject* target) { look_target_ = target; };
	void set_limit(Vector2 left_top, Vector2 bottom_right);//비출 수 있는 한계를 지정. 해상도로 자동 계산.
	void unset_limit() { is_limited_ = false; };
};

