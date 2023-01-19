#include "TitleText_Title.h"
#include "Core.h"
TitleText_Title::TitleText_Title()
	: Ui(true)
	, effect_state_(EFFECT_STATE::PREVIOUS)
{

}

TitleText_Title::~TitleText_Title()
{
}


void TitleText_Title::Update()
{
	Ui::Update();

	
	ChildrenUpdate();
}

void TitleText_Title::FinalUpdate()
{
	Ui::FinalUpdate();

	Vector2 current_pos = get_final_pos();
	if (remain_duration_ < 0) {
		effect_state_ = EFFECT_STATE::DONE;
		current_pos = dest_pos_;
	}
	else if (effect_state_ == EFFECT_STATE::PLAYING) {
		Vector2 scale = get_scale();
		Vector2 dist(dest_pos_.x - current_pos.x, 0.f);
		current_pos += (dist * DtF() / remain_duration_);
		remain_duration_ -= DtF();
	}

	set_pos(current_pos);

	ChildrenFinalUpdate();
}

void TitleText_Title::Render(ID3D11Device* p_d3d_device)
{
	Vector2 final_pos = get_final_pos();
	DrawAutosizeText(p_d3d_device, final_pos, get_scale(),
		_T("Harvest Moon"), _tcslen(_T("Harvest Moon")), _T("µÕ±Ù¸ð²Ã"), D2D1::ColorF::Black, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_WEIGHT_BOLD, 
		DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER, 100, 20, 2);
	ChildrenRender(p_d3d_device);
}

inline void TitleText_Title::StartEffect(Vector2 dest_pos, float duration)
{
	dest_pos_ = dest_pos;
	duration_ = duration;
	remain_duration_ = duration;
	effect_state_ = EFFECT_STATE::PLAYING;
}
