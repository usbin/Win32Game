#pragma once
#include "GObject.h"

class Missile : public GObject
{
private:
	Vector2 direction_;
	float speed_;
public:
	Missile();
	virtual ~Missile() override {};
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void OnCollisionEnter(const Collider& collider) override;

	inline void set_direction(const Vector2& v) { direction_ = v; };
	inline void set_speed(float speed) { speed_ = speed; };
};

