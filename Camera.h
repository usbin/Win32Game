#pragma once
#include "global.h"
class GObject;

class Camera
{
	SINGLETON(Camera);

private:
	Vector2 look_pos_ = Vector2::Zero();		//ī�޶� ���� ��ġ(�߽� ��ǥ)
	GObject* look_target_ = nullptr;	//Ÿ���� ������ ����


	Vector2 look_pos_dest_ = Vector2::Zero();	//õõ�� �������� ������ ��ġ
	float remain_second_ = 0;	//�����ϱ���� �� �� ���Ҵ���

public:
	void Update();
	Vector2 GetRenderPos(Vector2 world_pos);	//ī�޶� ���� ��ǥ
	Vector2 GetWorldPos(Vector2 render_pos);	//���� ��ǥ
	void MoveTo(Vector2 dest, float second);	//second�� ���� dest�� ����
	void set_look_pos(Vector2 look_pos) { look_pos_ = look_pos; };
	Vector2 get_look_pos() { return look_pos_; };
	void set_target(GObject* target) { look_target_ = target; };
};

