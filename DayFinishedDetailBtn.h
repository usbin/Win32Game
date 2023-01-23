#pragma once
#include "global.h"
#include "ButtonUi.h"
class DayFinishedDetailBtn : public ButtonUi
{
public:
	DayFinishedDetailBtn(bool is_static_pos) : ButtonUi(is_static_pos) {};
	void Init();
	void Render(ID3D11Device* p_d3d_device) override;
};

