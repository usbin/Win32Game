#pragma once
#include "GObject.h"

class RealObject : public GObject
{
public:
	RealObject();
	RealObject(const RealObject& origin);
	virtual ~RealObject();
	
private:

	Collider* collider_;		//�浹ü. ������ nullptr
	Animator* animator_;

	DIRECTION direction_;		//�ٶ󺸰� �ִ� ����


private:
	virtual void CreateCollider();
	virtual void CreateAnimator();
public:

	virtual void Update() override = 0;
	virtual void Render(ID3D11Device* p_d3d_device) override;
	virtual void FinalUpdate() override final;				// �浹ü �� �߰����� ������Ʈ���� Update �۾� ����
															// ������ GObject�� FinalUpdate�� ȣ��Ǿ�� ��.
															// �������̵� ����.
	virtual void ComponentRender(ID3D11Device* p_d3d_device) final;


	inline const DIRECTION get_direction() { return direction_; };
	inline void set_direction(DIRECTION direction) { direction_ = direction; };
	inline void set_collider(Collider* collider) { collider_ = collider; };
	inline Collider* get_collider() { return collider_; };
	inline void set_animator(Animator* animator) { animator_ = animator; };
	inline Animator* get_animator() { return animator_; };

	virtual void SaveToFile(FILE* p_file) override;
	virtual void LoadFromFile(FILE* p_file) override;

};

