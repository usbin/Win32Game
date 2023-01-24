#pragma once
#include "global.h"
#include "ButtonUi.h"
/// <summary>
/// YES, NO ¹öÆ°
/// </summary>
class AskSleepBtn : public ButtonUi
{
private:
	bool is_cursored_ = false;
	tstring text_;


public:
	AskSleepBtn(bool is_static_pos) :ButtonUi(is_static_pos) { };
	void Init(tstring text);
	void Render(ID3D11Device* p_d3d_device) override;

	void set_cursored(bool b) { is_cursored_ = b; };
};

