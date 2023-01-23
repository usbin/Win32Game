#pragma once
#include "global.h"
#include "Ui.h"
class DayFinishedDetailImgUi : public Ui
{
public:
	DayFinishedDetailImgUi(bool is_static_pos) :Ui(is_static_pos) {};
	void Init();
	void Render(ID3D11Device* p_d3d_device) override;
};

