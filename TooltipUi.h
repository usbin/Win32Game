#pragma once
#include "global.h"
#include "Ui.h"
class TooltipUi : public Ui
{
private:
	tstring text_;
public:
	TooltipUi(bool is_static_pos) :Ui(is_static_pos) {  };
	void Init(tstring text);
	void Update() override;
	void Render(ID3D11Device* p_d3d_device) override;

	void set_text(tstring text) { text_ = text; };
};

