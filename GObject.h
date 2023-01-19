#pragma once

#include "global.h"
//���� �ȿ� �����ϴ�, �׷����� �ϴ� ��� ������Ʈ
//�� ���������� �׷���.
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
	bool visible_ = true;	//�������� ���� ��, ������ �״��.(Render�� ����)
	bool enabled_ = true;	//false�� �� � �̺�Ʈ�� ���� �ʰ� �׷������� ����.
	DIRECTION direction_ = DIRECTION::DOWN;		//�ٶ󺸰� �ִ� ����


public:
	GObject();
	GObject(const GObject& origin); //���� ������
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
	inline void set_pos(Vector2 v) { //rect�� ����ȭ
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
	inline void SetDead() { is_dead_ = true; }; //EventManager�� ���ؼ��� ȣ���ؾ� ��. ���� �ܵ�ȣ��x.
	//�ܵ�ȣ�� �� �� EventManager�� dead_objects_�� �߰����� �ʰ� ���η�ƾ������ ���ܵǹǷ� ������ �������� ����.
	friend class EventManager;

};
