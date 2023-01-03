#pragma once
#include "RealObject.h"

class Missile : public RealObject
{
private:
	Vector2 direction_ = Vector2::Zero();
	float speed_ = 0;
public:
	Missile();
	virtual ~Missile() override {};
	virtual void Update() override;
	virtual void Render(ID3D11Device* p_d3d_device) override;
	virtual void OnCollisionEnter(Collider* collider) override;

	inline void set_direction(const Vector2& v) { direction_ = v; };
	inline void set_speed(float speed) { speed_ = speed; };
};

