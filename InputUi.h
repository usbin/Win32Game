#pragma once
#include "global.h"
#include "Ui.h"
struct OnInputEnterArgs {
	Ui* sender;
};
typedef void (*OnInputEnter)(tstring text, OnInputEnterArgs args);

class InputUi : public Ui
{
private:
	tstring hint_;
	tstring text_;
	Ui* owner_ = nullptr;
	OnInputEnter callback_ = nullptr;
	OnInputEnterArgs args_;

	float blink_time_ms_ = 0;
public:
	InputUi(bool is_static_pos) : Ui(is_static_pos) {};
	~InputUi();
	void Init(Ui* owner, OnInputEnter callback, OnInputEnterArgs args) { owner_ = owner; callback_ = callback; args_ = args; };
	void Update() override;
	void Render(ID3D11Device* p_d3d_device) override;
	void Select() override;
	void Unselect() override;
	void set_hint(tstring hint) { hint_ = hint; };
	tstring get_text() { return text_; };
};

