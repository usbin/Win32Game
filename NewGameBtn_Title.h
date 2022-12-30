#pragma once
#include "global.h"
#include "ButtonUi.h"
class NewGameBtn_Title : public ButtonUi
{
public:
	NewGameBtn_Title();
	~NewGameBtn_Title();

private:
	float text_alpha_;
	D2D1::ColorF text_color_;
	EFFECT_STATE effect_state_;
public:
	void StartEffect();
	virtual void Update();
	virtual void Render(ID3D11Device* p_d3d_device);
	void set_text_alpha(float alpha) { text_alpha_ = alpha; };
	EFFECT_STATE get_effect_state() { return effect_state_; };
};
