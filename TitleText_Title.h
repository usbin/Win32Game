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
	EFFECT_STATE effect_state_;
public:
	virtual void Update() override;
	virtual void FinalUpdate() override;
	virtual void Render(ID3D11Device* p_d3d_device);
	inline void StartEffect(Vector2 dest_pos, float duration);
	inline EFFECT_STATE get_effect_state() { return effect_state_; };
	
};

