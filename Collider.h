#pragma once
#include "global.h"
class GObject;

class Collider
{
public:
	Collider();
	~Collider();
	Collider(const Collider& org);

private:
	static UINT id_counter_;
	UINT id_;
	Vector2 pos_offset_;	//���� ������Ʈ�� pos�� �������� �� ������
	Vector2 scale_;			//ũ��
	Vector2 final_pos_;		//FinalUpdate���� ������Ʈ�ϴ� pos
	GObject* owner_;		//���� ������Ʈ
	int collision_count_;

public:
	inline UINT get_id() { return id_; };
	inline void set_pos_offset(const Vector2& pos) { pos_offset_ = pos; };
	inline const Vector2& get_pos_offset() { return pos_offset_; };
	inline void set_scale(const Vector2& scale) { scale_ = scale; };
	inline const Vector2& get_scale() { return scale_; };
	inline void set_owner(GObject* owner) { owner_ = owner; };
	inline const Vector2& get_pos() { return final_pos_; };

	void FinalUpdate();		//�� ������ ������Ʈ�� ���� �� owner�� ��ġ�� ����.
	void Render(HDC hdc);

	void OnCollisionEnter(const Collider& collider);
	void OnCollisionStay(const Collider& collider);
	void OnCollisionExit(const Collider& collider);

	Collider& operator=(const Collider& o_c) = delete;

};
