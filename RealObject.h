#pragma once
#include "GObject.h"

class RealObject : public GObject
{
public:
	RealObject();
	RealObject(const RealObject& origin);
	virtual ~RealObject();
	
private:

	Collider* collider_;		//충돌체. 없으면 nullptr
	Animator* animator_;

	DIRECTION direction_;		//바라보고 있는 방향


private:
	virtual void CreateCollider();
	virtual void CreateAnimator();
public:

	virtual void Update() override = 0;
	virtual void Render(ID3D11Device* p_d3d_device) override;
	virtual void FinalUpdate() override final;				// 충돌체 등 추가적인 컴포넌트들의 Update 작업 정의
															// 무조건 GObject의 FinalUpdate가 호출되어야 함.
															// 오버라이딩 방지.
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

