#pragma once
#include "global.h"
#include "Ui.h"
class DayFinishedDateUi : public Ui
{
private:
	UINT year_ = 0;
	UINT season_ = 0;
	UINT day_ = 0;

public:
	DayFinishedDateUi(bool is_static_pos) : Ui(is_static_pos) {};
	void Init(UINT year, UINT season, UINT day);
	void Render(ID3D11Device* p_d3d_device) override;
};

