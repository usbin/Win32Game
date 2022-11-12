#pragma once
#include "RealObject.h"

class Missile : public RealObject
{
private:
	Vector2 direction_;
	float speed_;
public:
	Missile();
	virtual ~Missile() override {};
	virtual void Update() override;
	virtual void Render(LPDIRECT3DDEVICE9 p_d3d_device) override;
	virtual void OnCollisionEnter(const Collider& collider) override;

	inline void set_direction(const Vector2& v) { direction_ = v; };
	inline void set_speed(float speed) { speed_ = speed; };
};

