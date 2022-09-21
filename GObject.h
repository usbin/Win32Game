#pragma once

#include "global.h"
//���� �ȿ� �����ϴ�, �׷����� �ϴ� ��� ������Ʈ
//�� ���������� �׷���.
class Collider;
class Animator;

class GObject
{
private:
	static unsigned int id_counter_;
	unsigned int id_;
	tstring name_;
	Vector2 pos_;
	Vector2 scale_;
	DIRECTION direction_;		//�ٶ󺸰� �ִ� ����
	SHORT priority_ = 0;		//������ �켱����. Ŭ���� ���߿� �׷���(set�� ���ʿ� ��ġ)
	GROUP_TYPE group_type_;
	Collider* collider_;		//�浹ü. ������ nullptr
	Animator* animator_;
	bool is_dead_;
	inline void SetDead() { is_dead_ = true; };

	virtual void CreateCollider();
	virtual void CreateAnimator();
public:
	GObject();
	GObject(const GObject& origin); //���� ������
	virtual ~GObject();
	SHORT priority() { return priority_; };
	virtual void Update()=0;
	virtual void FinalUpdate() final;	// �浹ü �� �߰����� ������Ʈ���� Update �۾� ����
										// ������ GObject�� FinalUpdate�� ȣ��Ǿ�� ��.
										// �������̵� ����.
	virtual void Render(HDC hdc)=0;
	virtual void ComponentRender(HDC hdc) final;
	virtual void OnCollisionEnter(const Collider& collider);
	virtual void OnCollisionStay(const Collider& collider);
	virtual void OnCollisionExit(const Collider& collider);

	unsigned long long get_id() { return id_; };
	inline void set_group_type(GROUP_TYPE type) { group_type_ = type; };
	inline GROUP_TYPE get_group_type() { return group_type_; };
	inline const Vector2& get_scale() { return scale_; };
	inline void set_scale(Vector2 scale) { scale_ = scale; };
	inline const DIRECTION get_direction() { return direction_; };
	inline void set_direction(DIRECTION direction) { direction_ = direction; };
	inline float get_width() { return scale_.x; };
	inline float get_height() { return scale_.y; };
	inline const Vector2& get_pos() { return pos_; }
	inline void set_pos(Vector2 v) { //rect�� ����ȭ
		float x_axis_dist = v.x - get_pos().x;
		float y_axis_dist = v.y - get_pos().y;
		pos_ = v;
	
	}
	inline GROUP_TYPE get_type() { return group_type_; };
	inline void set_collider(Collider* collider) { collider_ = collider; };
	inline Collider* get_collider() { return collider_; };
	inline void set_animator(Animator* animator) { animator_ = animator; };
	inline Animator* get_animator() { return animator_; };
	inline bool IsDead() { return is_dead_; };
	
	bool operator< (const GObject& o) const {
		if (this->priority_ != o.priority_) return this->priority_ < o.priority_;
		else return this->id_ < o.id_;
	};
	bool operator<= (const GObject& o) const {
		if (this->priority_ != o.priority_) return this->priority_ < o.priority_;
		else return this->id_ <= o.id_;
	};
	bool operator== (const GObject& o) const {
		return this->id_ == o.id_;
	}
	
	
	friend class EventManager;
};

struct GObjectPtCompare {
	const bool operator()(const GObject* o1, const GObject* o2) const {
		return (*o1) < (*o2);
	}
};