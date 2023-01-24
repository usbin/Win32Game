#include "DayFinishedDateUi.h"
#include "Decorator.h"
void DayFinishedDateUi::Init(UINT year, UINT season, UINT day)
{
	year_ = year;
	season_ = season;
	day_ = day;
}

void DayFinishedDateUi::Render(ID3D11Device* p_d3d_device)
{
	Decorator::GetInstance()->GetSimpleFrame()->Render(p_d3d_device, this, RENDER_LAYER::TOP);


	TCHAR buffer[30];
	memset(buffer, 0, sizeof(buffer));

	tstring season;
	switch (season_) {
	case 0: season = _T("봄");
		break;
	case 1: season = _T("여름");
		break;
	case 2: season = _T("가을");
		break;
	case 3: season = _T("겨울");
		break;
	}
	_stprintf_s(buffer, _T("%d년째, %s의 %d일째"), year_, season.c_str(), day_);
	
	DrawFixedsizeText(p_d3d_device, get_final_pos(), get_scale()
		, buffer, _tcslen(buffer), _T("둥근모꼴"), 30
		, D2D1::ColorF::Black, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_WEIGHT_NORMAL
		, DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER
		, RENDER_LAYER::TOP);

}
