#include "NewGameBtn_Title.h"
#include "Ui.h"
#include "Core.h"

NewGameBtn_Title::NewGameBtn_Title()
	: ButtonUi(true)
	, text_color_(D2D1::ColorF::Black)
	, text_alpha_(0.f)
	, effect_state_(EFFECT_STATE::PREVIOUS)
{

	text_color_.a = 0.f;
}

NewGameBtn_Title::~NewGameBtn_Title()
{
}

void NewGameBtn_Title::StartEffect()
{
	effect_state_ = EFFECT_STATE::PLAYING;
}

void NewGameBtn_Title::Update()
{
	ButtonUi::Update();

	if (effect_state_ == EFFECT_STATE::PLAYING) {
		text_alpha_ += DtF();
		if (text_alpha_ > 1.0f) {
			text_alpha_ = 1.0f;
			effect_state_ = EFFECT_STATE::DONE;
		}
	}
	text_color_.a = text_alpha_;
	ChildrenUpdate();
	
}

void NewGameBtn_Title::Render(ID3D11Device* p_d3d_device)
{
	if (get_visible()) {
		DrawRectangle(p_d3d_device, get_final_pos(), get_scale(), ARGB(0xFFEEEEEE), 1);
		DrawFixedsizeText(p_d3d_device
			, get_final_pos(), get_scale()
			, _T("새 게임"), _tcsclen(_T("새 게임")), _T("둥근모꼴"), 30, text_color_, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_WEIGHT_BOLD
			, DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}
	
}
