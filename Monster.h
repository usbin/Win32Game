#pragma once
#include "RealObject.h"

class Monster : public RealObject
{
private:
	float move_speed_ = 0;
	Vector2 center_pos_ = Vector2::Zero();
	float move_range_ = 0;
	int direction_ = 0; //-1¿Þ 1¿À
public:
	Monster();
	virtual ~Monster() override;
	virtual void CreateInteractor() override;
	virtual void Update() override;
	virtual void Render(ID3D11Device* p_d3d_device) override;
	virtual void OnInteract(const GObject* req_obj) override;
	inline void set_move_speed(float speed) { move_speed_ = speed; };
	inline void set_center_pos(Vector2 pos) { center_pos_ = pos; };
	inline void set_move_range(float range) { move_range_ = range; };

};

