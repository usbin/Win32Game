#pragma once
#include "global.h"
#include "Ui.h"
class InputUi;
class DebugConsoleUi : public Ui
{
private:
	std::deque<tstring> log_;
	Vector2 log_offset_;
	Vector2 log_scale_;
public:
	DebugConsoleUi(bool is_static_pos) : Ui(is_static_pos) {};
	void Init();
	void Update() override;
	void Render(ID3D11Device* p_d3d_device) override;
	void OnInput(tstring text);
	void PrintConsole(tstring text);
	void Excute(std::vector<tstring>& commands);
};

