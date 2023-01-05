#pragma once
#include "global.h"
class Texture;
class Animator;
struct AnimationFrame {
	Vector2 base_pos;
	Vector2 img_size;
};
class Animation
{
public:
	Animation();
	virtual ~Animation();
private:
	Animator* animator_ = nullptr;
	

protected:
	tstring name_;
	float duration_ = 0;
	bool is_repeat_ = false;		//�ݺ���� ����
	int img_count_ = 0;
	Vector2 offset_ = Vector2::Zero();		//GObject�� ���� �׷����� �ִϸ��̼ǰ��� �Ÿ�
	bool is_finished_ = false;		//����� �������� ����
	float frame_acc_dt_ = 0;	//���� ������ ���� �� ����� �ð�
	int frame_index_ = 0;

	Texture* texture_ = nullptr;
	std::vector<AnimationFrame> frames_;

	
public:
	void Init(tstring name, Texture* texture, Vector2 base_pos, Vector2 img_size, Vector2 img_distance, Vector2 offset
		, float duration, int img_count, bool is_repeat);
	void Update();
	virtual void Render(ID3D11Device* p_d3d_device) = 0;
	void ResetFrame();	//�������� 0��°�� �ǵ����� �Լ�(�����)
	inline void set_animator(Animator* animator) { animator_ = animator; };
	inline tstring& get_name() { return name_; };
	inline bool is_repeat() { return is_repeat_; };
	inline bool is_finished() { return is_finished_; };
	Animator* get_animator() { return animator_; };

};

