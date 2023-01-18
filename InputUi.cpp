#include "InputUi.h"
#include "UiManager.h"
#include "Time.h"
#include "Game.h"
InputUi::~InputUi()
{
}
void InputUi::Update()
{
	Ui::Update();

	if (KEY_DOWN(KEY::Q))
		text_ += _T("Q");
	if (KEY_DOWN(KEY::W)) text_ += _T("W");
	if (KEY_DOWN(KEY::E)) text_ += _T("E");
	if (KEY_DOWN(KEY::R)) text_ += _T("R");
	if (KEY_DOWN(KEY::T)) text_ += _T("T");
	if (KEY_DOWN(KEY::Y)) text_ += _T("Y");
	if (KEY_DOWN(KEY::U)) text_ += _T("U");
	if (KEY_DOWN(KEY::I)) text_ += _T("I");
	if (KEY_DOWN(KEY::O)) text_ += _T("O");
	if (KEY_DOWN(KEY::P)) text_ += _T("P");
	if (KEY_DOWN(KEY::A)) text_ += _T("A");
	if (KEY_DOWN(KEY::S)) text_ += _T("S");
	if (KEY_DOWN(KEY::D)) text_ += _T("D");
	if (KEY_DOWN(KEY::F)) text_ += _T("F");
	if (KEY_DOWN(KEY::G)) text_ += _T("G");
	if (KEY_DOWN(KEY::H)) text_ += _T("H");
	if (KEY_DOWN(KEY::J)) text_ += _T("J");
	if (KEY_DOWN(KEY::K)) text_ += _T("K");
	if (KEY_DOWN(KEY::L)) text_ += _T("L");
	if (KEY_DOWN(KEY::Z)) text_ += _T("Z");
	if (KEY_DOWN(KEY::X)) text_ += _T("X");
	if (KEY_DOWN(KEY::C)) text_ += _T("C");
	if (KEY_DOWN(KEY::V)) text_ += _T("V");
	if (KEY_DOWN(KEY::B)) text_ += _T("B");
	if (KEY_DOWN(KEY::N)) text_ += _T("N");
	if (KEY_DOWN(KEY::M)) text_ += _T("M");
	if (KEY_DOWN(KEY::KEY_PLUS)) text_	+= _T("+");
	if (KEY_DOWN(KEY::KEY_MINUS)) text_ += _T("-");
	if (KEY_DOWN(KEY::SPACE)) text_		+= _T(" ");
	if (KEY_DOWN(KEY::BACKSPACE)) text_.erase(text_.end() - 1);
	if (KEY_DOWN(KEY::ENTER)) {
		if(callback_)
			callback_(text_, args_);
		text_ = _T("");
	}
	if (KEY_DOWN(KEY::KEY_0)) text_ += _T("0");
	if (KEY_DOWN(KEY::KEY_1)) text_ += _T("1");
	if (KEY_DOWN(KEY::KEY_2)) text_ += _T("2");
	if (KEY_DOWN(KEY::KEY_3)) text_ += _T("3");
	if (KEY_DOWN(KEY::KEY_4)) text_ += _T("4");
	if (KEY_DOWN(KEY::KEY_5)) text_ += _T("5");
	if (KEY_DOWN(KEY::KEY_6)) text_ += _T("6");
	if (KEY_DOWN(KEY::KEY_7)) text_ += _T("7");
	if (KEY_DOWN(KEY::KEY_8)) text_ += _T("8");
	if (KEY_DOWN(KEY::KEY_9)) text_ += _T("9");

	
	
}

void InputUi::Render(ID3D11Device* p_d3d_device)
{
	//0.7초마다 깜빡이는 커서
	tstring text_with_blink = text_;
	blink_time_ms_ += Time::GetInstance()->dt_f();
	if (blink_time_ms_ < .7f) {
		text_with_blink = text_ + _T("|");
	}
	if (blink_time_ms_ > 1.4f) {
		blink_time_ms_ = 0.f;
	}
	//hint 출력
	if (text_.empty()) {
		DrawAutosizeText(p_d3d_device, get_final_pos(), get_scale()
			, hint_.c_str(), hint_.size() + 1, _T("둥근모꼴"), D2D1::ColorF::DarkGray
			, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT_CENTER, 30, 12, 1, RENDER_LAYER::TOP);
	}
	//text+ blink 커서 출력
	DrawAutosizeText(p_d3d_device, get_final_pos(), get_scale()
		, text_with_blink.c_str(), text_with_blink.size() + 1, _T("둥근모꼴"), D2D1::ColorF::White
		, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT_CENTER, 30, 12, 1, RENDER_LAYER::TOP);
	
	
	

}

void InputUi::Select()
{
	Game::GetInstance()->ControlFreeze();
}

void InputUi::Unselect()
{
	Game::GetInstance()->ControlUnfreeze();

}
