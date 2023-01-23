#pragma once
#include "global.h"
#include "Ui.h"
class DayFinishedInfoContainerUi : public Ui
{
private:
	tstring text_;
	UINT gold_;
public:
	DayFinishedInfoContainerUi(bool is_static_pos) : Ui(is_static_pos) {};
	void Init(tstring text, UINT gold);
	void Render(ID3D11Device* p_d3d_device) override;

}; 

