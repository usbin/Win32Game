#include "Loading.h"
#include "Core.h"
#include "Time.h"
void Loading::Update()
{
	timer_ += Time::GetInstance()->dt_f();
	if (timer_ > 2.0) timer_ = 0.f;

}
void Loading::Render(ID3D11Device* p_d3d_device)
{
	DrawRectangle(p_d3d_device, Vector2::Zero(), Core::GetInstance()->get_resolution(), ARGB(0xFF000000), 1, ARGB(0xFF000000), RENDER_LAYER::TOP);
	TCHAR text[50];
	_stprintf_s(text, _T("%s"), _T("Loading"));
	for (int i = 0; i < (int)(timer_ / .5f); i++) {
		_tcscat_s(text, _T("."));
	}
	DrawFixedsizeText(p_d3d_device, Vector2::Zero(), Core::GetInstance()->get_resolution()
		, text, _tcslen(text), _T("µÕ±Ù¸ð²Ã"), 20
		, D2D1::ColorF::White, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_WEIGHT_NORMAL
		, DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER
		, RENDER_LAYER::TOP);
}
