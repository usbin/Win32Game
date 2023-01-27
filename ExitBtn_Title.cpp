#include "ExitBtn_Title.h"
#include "Decorator.h"
#include "Time.h"
void ExitBtn_Title::StartEffect(float delay)
{
	effect_state_ = EFFECT_STATE::PLAYING;
	delay_ = delay;
}

void ExitBtn_Title::Update()
{
	ButtonUi::Update();

	if (effect_state_ == EFFECT_STATE::PLAYING) {
		delay_ -= Time::GetInstance()->dt_f();
		if (delay_ < 0) {
			visible_ = true;
			effect_state_ = EFFECT_STATE::DONE;

		}
	}
}

void ExitBtn_Title::Render(ID3D11Device* p_d3d_device)
{
	if (visible_) {
		Decorator::GetInstance()->GetSimpleFrame()->Render(p_d3d_device, this, RENDER_LAYER::GROUND);
		DrawFixedsizeText(p_d3d_device
			, get_final_pos(), get_scale()
			, _T("나가기"), _tcsclen(_T("나가기")), _T("둥근모꼴"), 30, D2D1::ColorF::Black, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_WEIGHT_BOLD
			, DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}
}
