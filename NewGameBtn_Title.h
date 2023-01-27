#pragma once
#include "global.h"
#include "ButtonUi.h"
class NewGameBtn_Title : public ButtonUi
{
public:
	NewGameBtn_Title();
	~NewGameBtn_Title();

private:
	bool visible_ = false;
	EFFECT_STATE effect_state_ = EFFECT_STATE::PREVIOUS;
	float delay_ = 0.f;
public:
	void StartEffect(float delay);
	virtual void Update();
	virtual void Render(ID3D11Device* p_d3d_device);
	EFFECT_STATE get_effect_state() { return effect_state_; };
};

