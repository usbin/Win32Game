#pragma once
#include "GObject.h"

class Interactor;
class ControlComponent;
class PhysicsComponent;
class RealObject : public GObject
{
public:
	RealObject();
	RealObject(const RealObject& origin);
	virtual ~RealObject();
	
protected:

	Collider* collider_;		//충돌체. 없으면 nullptr
	Animator* animator_;
	Interactor* interactor_;	//상호작용체.
	ControlComponent* control_cmp_;
	PhysicsComponent* physics_cmp_;
	Vector2 velocity_;


protected:
	virtual void CreateCollider() {};
	virtual void CreateAnimator() {};
	virtual void CreateInteractor() {};
	virtual void CreateControlCmp() {};
	virtual void CreatePhysicsCmp() {};
public:

	virtual void Update() override = 0;
	virtual void Render(ID3D11Device* p_d3d_device) override;
	virtual void FinalUpdate() override	final;					
	virtual void ComponentRender(ID3D11Device* p_d3d_device) final;


	inline void set_collider(Collider* collider) { collider_ = collider; };
	inline Collider* get_collider() { return collider_; };
	inline void set_interactor(Interactor* interactor) { interactor_ = interactor; };
	inline Interactor* get_interactor() { return interactor_; };
	inline void set_animator(Animator* animator) { animator_ = animator; };
	inline Animator* get_animator() { return animator_; };
	inline void set_velocity(Vector2 velocity) { velocity_ = velocity; };
	inline Vector2 get_velocity() { return velocity_; };
	virtual void SaveToFile(FILE* p_file) override;
	virtual void LoadFromFile(FILE* p_file) override;

	friend class PhysicsComponent;


};

