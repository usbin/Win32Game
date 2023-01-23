#include "DayFinishedInfoContainerUi.h"
#include "Decorator.h"
void DayFinishedInfoContainerUi::Init(tstring text, UINT gold)
{
	text_ = text;
	gold_ = gold;
}
void DayFinishedInfoContainerUi::Render(ID3D11Device* p_d3d_device)
{
	Decorator::GetInstance()->GetSimpleFrame()->Render(p_d3d_device, this, RENDER_LAYER::PLAYER);
	TCHAR buffer[20];
	_stprintf_s(buffer, _T("%dG"), gold_);
	DrawFixedsizeText(p_d3d_device, get_final_pos() + Vector2{ 10, -5 }, get_scale()
		, text_.c_str(), text_.size() + 1, _T("µÕ±Ù¸ð²Ã"), 36
		, D2D1::ColorF::Black, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_WEIGHT_NORMAL
		, DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT_CENTER
		, RENDER_LAYER::PLAYER);

	DrawFixedsizeText(p_d3d_device, get_final_pos() + Vector2{ get_scale().x - 300.f, -5.f }, Vector2{280.f, get_scale().y}
		, buffer, _tcslen(buffer), _T("µÕ±Ù¸ð²Ã"), 36
		, D2D1::ColorF::Black, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_WEIGHT_NORMAL
		, DWRITE_TEXT_ALIGNMENT_TRAILING, DWRITE_PARAGRAPH_ALIGNMENT_CENTER
		, RENDER_LAYER::PLAYER);
}
