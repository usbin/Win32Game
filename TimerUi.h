#pragma once
#include "global.h"
#include "Ui.h"

class TimerUi : public Ui
{
public:
	TimerUi();
	~TimerUi() {};

	virtual void Update() override;
	virtual void Render(ID3D11Device* p_d3d_device) override;
};

