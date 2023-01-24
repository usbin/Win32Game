#pragma once
#include "global.h"
#include "ButtonUi.h"
class DayFinishedOkBtn : public ButtonUi
{
public:
	DayFinishedOkBtn(bool is_static_pos) : ButtonUi(is_static_pos) {};
	void Render(ID3D11Device* p_d3d_device) override;
};

