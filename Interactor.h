#pragma once
#include "global.h"
#include "Collider.h"
#include "RealObject.h"

class Interactor : public RealObject
{
public:
	Interactor();
	~Interactor();

private:
	GObject* owner_ = nullptr;
	std::vector<Interactor*> interactors_;
	Vector2 pos_offset_ = Vector2::Zero();


public:
	void Init(GObject* owner, Vector2 pos_offset, Vector2 scale);

	inline const std::vector<Interactor*>& get_interactors() { return interactors_; }; //������ ���ͷ��� ��� ��ȯ

	// GObject��(��) ���� ��ӵ�
public:
	virtual void Update() override;
	virtual void Render(ID3D11Device* p_d3d_device) override;
	virtual void OnCollisionEnter(Collider* collider) override;
	virtual void OnCollisionExit(Collider* collider) override;
	void set_scale(Vector2 scale) = delete;
	Vector2 get_scale() = delete;
	inline void set_owner(GObject* owner) { owner_ = owner; };
	inline GObject* get_owner() { return owner_; };
	inline void OnInteract(const GObject* obj) override;
	friend class GObject;


};

