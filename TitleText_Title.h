#pragma once
#include "global.h"
#include "Ui.h"
class TitleText_Title : public Ui
{
public:
	TitleText_Title();
	~TitleText_Title();
private:
	Vector2 dest_pos_;
	float duration_;
	float remain_duration_;
public:
	virtual void Update();
	virtual void Render(ID3D11Device* p_d3d_device);
	inline bool IsAnimationDone() { return remain_duration_ > std::numeric_limits<float>::epsilon(); };
	inline void set_dest_pos(Vector2 pos) { dest_pos_ = pos; }
	inline void set_duration(float duration) { duration_ = duration; }
};

