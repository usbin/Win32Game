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
	bool is_repeat_ = false;		//반복재생 여부
	int img_count_ = 0;
	Vector2 offset_ = Vector2::Zero();		//GObject와 실제 그려지는 애니메이션간의 거리
	bool is_finished_ = false;		//재생이 끝났는지 여부
	float frame_acc_dt_ = 0;	//현재 프레임 실행 후 경과된 시간
	int frame_index_ = 0;

	Texture* texture_ = nullptr;
	std::vector<AnimationFrame> frames_;

	
public:
	void Init(tstring name, Texture* texture, Vector2 base_pos, Vector2 img_size, Vector2 img_distance, Vector2 offset
		, float duration, int img_count, bool is_repeat);
	void Update();
	virtual void Render(ID3D11Device* p_d3d_device) = 0;
	void ResetFrame();	//프레임을 0번째로 되돌리는 함수(재시작)
	inline void set_animator(Animator* animator) { animator_ = animator; };
	inline tstring& get_name() { return name_; };
	inline bool is_repeat() { return is_repeat_; };
	inline bool is_finished() { return is_finished_; };
	Animator* get_animator() { return animator_; };

};

