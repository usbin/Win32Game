#pragma once
#include "global.h"
#include "Ui.h"
class AskSleepBtn;
class AskSleepUi : public Ui
{
private:
	const int CURSOR_YES = 0;
	const int CURSOR_NO = 1;

	int cursor_ = 0;
	AskSleepBtn* btns_[2];

public:
	AskSleepUi(bool is_static_pos);
	~AskSleepUi();
	void Init();
	void Update() override;
	void Render(ID3D11Device* p_d3d_device) override;
	
};

