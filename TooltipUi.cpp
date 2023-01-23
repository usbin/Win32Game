#include "TooltipUi.h"
#include "Decorator.h"

#define TOOLTIP_MAX_WIDTH 400
#define FONT_SIZE 20
void TooltipUi::Init(tstring text)
{
	text_ = text;
}

void TooltipUi::Update()
{
	//text_ 길이에 맞춰서 가로는 최대 400, 세로는 최대 2줄까지 늘림.
	int required_width = (FONT_SIZE) * text_.size() + 40.f;	
	int required_height = (1 + required_width / TOOLTIP_MAX_WIDTH) * (FONT_SIZE) + 40.f;
	set_scale(Vector2{ required_width, required_height });
}

void TooltipUi::Render(ID3D11Device* p_d3d_device)
{
	if (text_.length() > 0) {
		Decorator::GetInstance()->GetSimpleFrame()->Render(p_d3d_device, this, RENDER_LAYER::TOP);
		Vector2 pos = is_static_pos() ? get_final_pos() : WorldToRenderPos(get_final_pos());
		DrawFixedsizeText(p_d3d_device, pos + Vector2{ 20, 20 }, get_scale(), text_.c_str(), text_.size() + 1, _T("둥근모꼴"), FONT_SIZE, D2D1::ColorF::Black
			, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT_NEAR
			, RENDER_LAYER::TOP);
	}
	
}
