#pragma once

#include "global.h"
//게임 안에 존재하는, 그려져야 하는 모든 오브젝트
//매 렌더링에서 그려줌.
class Collider;
class Animator;
class Sprite;

class GObject
{
private:
	static unsigned int id_counter_;
	unsigned int id_;
	tstring name_;
	Vector2 pos_;
	Vector2 scale_;
	GROUP_TYPE group_type_;
	bool is_dead_;

	Sprite* sprite_;


public:
	GObject();
	GObject(const GObject& origin); //복사 생성자
	virtual ~GObject();
	virtual void Update()=0;
	virtual void FinalUpdate() {};
	virtual void Render(HDC hdc)=0;
	virtual void OnCollisionEnter(const Collider& collider) {};
	virtual void OnCollisionStay(const Collider& collider) {};
	virtual void OnCollisionExit(const Collider& collider) {};

	unsigned long long get_id() { return id_; };
	inline const tstring& get_name() { return name_; };
	inline void set_name(const tstring& name) { name_ = name; };
	inline void set_group_type(GROUP_TYPE type) { group_type_ = type; };
	inline GROUP_TYPE get_group_type() { return group_type_; };
	inline const Vector2& get_scale() { return scale_; };
	inline void set_scale(Vector2 scale) { scale_ = scale; };
	inline float get_width() { return scale_.x; };
	inline float get_height() { return scale_.y; };
	inline const Vector2& get_pos() const { return pos_; }
	inline void set_pos(Vector2 v) { //rect도 동기화
		float x_axis_dist = v.x - get_pos().x;
		float y_axis_dist = v.y - get_pos().y;
		pos_ = v;
	
	}
	inline GROUP_TYPE get_type() { return group_type_; };
	inline Sprite* get_sprite() { return sprite_; };
	void ChangeSprite(Sprite* sprite);

	inline void SetDead() { is_dead_ = true; };
	inline bool IsDead() { return is_dead_; };

	
	bool operator== (const GObject& o) const {
		return this->id_ == o.id_;
	}
	
	
	friend class EventManager;
};
