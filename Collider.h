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
	UINT id_ = 0;
	Vector2 pos_offset_ = Vector2::Zero();		//���� ������Ʈ�� pos�� �������� �� ������
	Vector2 scale_ = Vector2::Zero();				//ũ��
	Vector2 final_pos_ = Vector2::Zero();			//FinalUpdate���� ������Ʈ�ϴ� pos
	GObject* owner_ = nullptr;			//���� ������Ʈ

	bool is_physical_collider_ = false;	//������Ģ�� ������ �޴°�(�浹 �˻縸 �ϴ°�, �浹�� �̵��� �����ϴ°�)
	std::vector<Collider*> physical_collisions_;
	

public:
	inline UINT get_id() { return id_; };
	inline void set_pos_offset(Vector2 pos) { pos_offset_ = pos; };
	inline Vector2 get_pos_offset() { return pos_offset_; };
	inline void set_scale(Vector2 scale) { scale_ = scale; };
	inline Vector2 get_scale() { return scale_; };
	inline void set_owner(GObject* owner) { owner_ = owner; };
	inline GObject* get_owner() const { return owner_; };
	inline Vector2 get_pos() { return final_pos_; };
	inline void set_is_physical_collider(bool b) { is_physical_collider_ = b; };
	inline bool get_is_physical_collider() { return is_physical_collider_; };
	inline const std::vector<Collider*>& get_physical_collisions() { return physical_collisions_; };

	void FinalUpdate();		//�� ������ ������Ʈ�� ���� �� owner�� ��ġ�� ����.
	void Render(ID3D11Device* p_d3d_device);

	void OnCollisionEnter(Collider* collider);
	void OnCollisionStay(Collider* collider);
	void OnCollisionExit(Collider* collider);

	Collider& operator=(const Collider& o_c) = delete;



};

