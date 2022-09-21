#pragma once
#include "global.h"
class GObject;

class Camera
{
	SINGLETON(Camera);

private:
	Vector2 look_pos_;		//ī�޶� ���� ��ġ(�߽� ��ǥ)
	GObject* look_target_;	//Ÿ���� ������ ����


	Vector2 look_pos_dest_;	//õõ�� �������� ������ ��ġ
	float remain_second_;	//�����ϱ���� �� �� ���Ҵ���

public:
	void Update();
	Vector2 GetRenderPos(Vector2 obj_pos);	//ī�޶� ���� ��ǥ
	Vector2 GetWorldPos(Vector2 obj_pos);	//��ü ���� ���� ��ǥ
	void MoveTo(Vector2 dest, float second);	//second�� ���� dest�� ����
	void set_look_pos(Vector2 look_pos) { look_pos_ = look_pos; };
	Vector2 get_look_pos() { return look_pos_; };
	void set_target(GObject* target) { look_target_ = target; };
};
