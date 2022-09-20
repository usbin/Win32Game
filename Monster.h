#pragma once
#include "GObject.h"

class Monster : public GObject
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
	virtual void Render(HDC hdc) override;
	inline void set_move_speed(float speed) { move_speed_ = speed; };
	inline void set_center_pos(Vector2 pos) { center_pos_ = pos; };
	inline void set_move_range(float range) { move_range_ = range; };

};

