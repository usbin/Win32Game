#pragma once
#include "GObject.h"
#include "RealObjectRenderComponent.h"
#include "RealObjectSprite.h"
class Interactor;
class IControlComponent;
class PhysicsComponent;
class IRenderComponent;
class IItemHolder;
class RealObject : public GObject
{
public:
	RealObject();
	RealObject(const RealObject& origin);
	virtual ~RealObject();
	
protected:

	Collider* collider_ = nullptr;		//충돌체. 없으면 nullptr
	Interactor* interactor_ = nullptr;	//상호작용체.(GObject를 물려받아 생명주기 관리x)
	IControlComponent* control_cmp_ = nullptr;
	PhysicsComponent* physics_cmp_ = nullptr;
	IRenderComponent* render_cmp_ = nullptr;
	Vector2 velocity_ = Vector2::Zero();

	IItemHolder* item_holder_ = nullptr;

protected:
	virtual void CreateCollider() {};
	virtual void CreateAnimator() {};
	virtual void CreateInteractor() {};
	virtual void CreateControlCmp() {};
	virtual void CreatePhysicsCmp() {};
	virtual void CreateRenderCmp() {};
public:

	virtual void Update() override = 0;
	virtual void Render(ID3D11Device* p_d3d_device) override;
	virtual void FinalUpdate() override	final;					
	virtual void ComponentRender(ID3D11Device* p_d3d_device) final;

	virtual void OnUseItem(ITEM_CODE item_code) {};
	inline void set_collider(Collider* collider) { collider_ = collider; };
	inline Collider* get_collider() { return collider_; };
	inline void set_interactor(Interactor* interactor) { interactor_ = interactor; };
	inline Interactor* get_interactor() { return interactor_; };
	inline void set_control_component(IControlComponent* cmp) { control_cmp_ = cmp; };
	inline IControlComponent* get_control_component() { return control_cmp_; };
	inline void set_physics_component(PhysicsComponent* cmp) { physics_cmp_ = cmp; };
	inline PhysicsComponent* get_physics_component() { return physics_cmp_; };
	inline IRenderComponent* get_render_component() { return render_cmp_; };
	inline void set_render_component(IRenderComponent* cmp) { render_cmp_ = cmp; };
	inline void set_velocity(Vector2 velocity) { velocity_ = velocity; };
	inline Vector2 get_velocity() { return velocity_; };
	virtual ISprite* get_sprite() { return render_cmp_ ? dynamic_cast<ISprite*>(render_cmp_->get_sprite()) : nullptr; };
	inline IItemHolder* get_item_holder() const { return item_holder_; };

	virtual void MoveTo(GObject* gobject) override;

	friend class PhysicsComponent;


};

