#include "TitleText_Title.h"
#include "Core.h"
TitleText_Title::TitleText_Title()
	: Ui(true)
{
	//초기 위치 : 화면 밖
	Vector2 scale = Vector2(1000, 200);
	Vector2 resolution = Core::GetInstance()->get_resolution();
	set_pos(Vector2(resolution.x, resolution.y/4.f));
	set_scale(scale);
	dest_pos_ = get_pos();
}

TitleText_Title::~TitleText_Title()
{
}


void TitleText_Title::Update()
{
	Ui::Update();

	Vector2 current_pos = get_pos();
	if (dest_pos_.x-current_pos.x > std::numeric_limits<float>::epsilon()) {
		// 우측에서 나타나 중앙으로 이동
		Vector2 scale = get_scale();
		Vector2 dist((dest_pos_.x / 2.f - scale.x / 2.f) - current_pos.x, 0.f);
		current_pos += dist / remain_duration_;
		remain_duration_ -= DtF();
		set_pos(current_pos);
	}
	
	ChildrenUpdate();
}

void TitleText_Title::Render(ID3D11Device* p_d3d_device)
{
	Vector2 final_pos = get_final_pos();
	DrawAutosizeText(p_d3d_device, final_pos, get_scale(),
		_T("Harvest Moon"), _tcslen(_T("Harvest Moon")), _T("둥근모꼴"), D2D1::ColorF::Black, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_WEIGHT_BOLD, 
		DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER, 200, 20, 2);

	ChildrenRender(p_d3d_device);
}
