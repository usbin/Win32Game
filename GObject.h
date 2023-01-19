#pragma once

#include "global.h"
//게임 안에 존재하는, 그려져야 하는 모든 오브젝트
//매 렌더링에서 그려줌.
class Collider;
class Animator;
class ISprite;

class GObject
{
private:
	static unsigned int id_counter_;
	unsigned int id_;
	tstring name_;
	Vector2 pos_ = Vector2::Zero();
	Vector2 scale_ = Vector2::Zero();
	GROUP_TYPE group_type_;
	bool is_dead_ = false;
	bool visible_ = true;	//보이지만 않을 뿐, 동작은 그대로.(Render만 제외)
	bool enabled_ = true;	//false일 땐 어떤 이벤트도 받지 않고 그려지지도 않음.
	DIRECTION direction_ = DIRECTION::DOWN;		//바라보고 있는 방향


public:
	GObject();
	GObject(const GObject& origin); //복사 생성자
	virtual ~GObject();
	virtual void Update()=0;
	virtual void FinalUpdate() {};
	virtual void Render(ID3D11Device* p_d3d_device)=0;
	virtual void OnCollisionEnter(Collider* collider) {};
	virtual void OnCollisionStay(Collider* collider) {};
	virtual void OnCollisionExit(Collider* collider) {};
	virtual void OnInteract(const GObject* req_obj) {};

	unsigned long long get_id() { return id_; };
	inline const tstring& get_name() { return name_; };
	inline void set_name(const tstring& name) { name_ = name; };
	inline void set_group_type(GROUP_TYPE type) { group_type_ = type; };
	inline GROUP_TYPE get_group_type() const { return group_type_; };
	inline Vector2 get_scale() { return scale_; };
	inline void set_scale(Vector2 scale) { scale_ = scale; };
	inline float get_width() { return scale_.x; };
	inline float get_height() { return scale_.y; };
	inline Vector2 get_pos() { return pos_; }
	inline void set_pos(Vector2 v) { //rect도 동기화
		pos_ = v;
	
	}
	inline GROUP_TYPE get_type() { return group_type_; };
	inline bool IsDead() { return is_dead_; };
	inline void set_visible(bool b) { visible_ = b; };
	inline bool get_visible() { return visible_; };
	inline bool get_enabled() { return enabled_; };
	inline void set_enabled(bool b) { enabled_ = b; OnEnabled(b); };
	virtual void OnEnabled(bool b) {};
	inline const DIRECTION get_direction() { return direction_; };
	inline void set_direction(DIRECTION direction) { direction_ = direction; };

	
	bool operator== (const GObject& o) const {
		return this->id_ == o.id_;
	}
	
	




private:
	inline void SetDead() { is_dead_ = true; }; //EventManager를 통해서만 호출해야 함. 절대 단독호출x.
	//단독호출 할 시 EventManager의 dead_objects_에 추가되지 않고 메인루틴에서도 제외되므로 영원히 삭제되지 않음.
	friend class EventManager;

};
