#include "AskSleepBtn.h"

void AskSleepBtn::Init(tstring text)
{
	text_ = text;
}

void AskSleepBtn::Render(ID3D11Device* p_d3d_device)
{
	DrawFixedsizeText(p_d3d_device, get_final_pos(), get_scale()
		, text_.c_str(), text_.size() + 1, _T("µÕ±Ù¸ð²Ã"), 20
		, D2D1::ColorF::Black, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_WEIGHT_NORMAL
		, DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER
		, RENDER_LAYER::PLAYER);
	if (is_cursored_) {
		DrawRectangle(p_d3d_device, get_final_pos(), get_scale(), ARGB(0xFFFF0000), 2, RENDER_LAYER::PLAYER);
	}
}
