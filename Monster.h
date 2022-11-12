#pragma once
#include "RealObject.h"

class Monster : public RealObject
{
private:
	float move_speed_;
	Vector2 center_pos_;
	float move_range_;
	int direction_; //-1¿Þ 1¿À
public:
	Monster();
	virtual ~Monster() override;
	virtual void Update() override;
	virtual void Render(LPDIRECT3DDEVICE9 p_d3d_device) override;
	inline void set_move_speed(float speed) { move_speed_ = speed; };
	inline void set_center_pos(Vector2 pos) { center_pos_ = pos; };
	inline void set_move_range(float range) { move_range_ = range; };

};

