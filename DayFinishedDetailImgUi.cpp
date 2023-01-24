#include "DayFinishedDetailImgUi.h"
#include "Decorator.h"
#include "UiSprite.h"
void DayFinishedDetailImgUi::Init()
{
}

void DayFinishedDetailImgUi::Render(ID3D11Device* p_d3d_device)
{
	Decorator::GetInstance()->GetSimpleFrame()->Render(p_d3d_device, this, RENDER_LAYER::TOP);
	if (get_sprite()) {
		DrawTexture(p_d3d_device, get_final_pos() + Vector2{ 10, 10 }, get_scale() - Vector2{ 20, 20 }, get_sprite()->get_base_pos(), get_sprite()->get_scale(), get_sprite()->get_texture(), RENDER_LAYER::TOP);
	}
	ChildrenRender(p_d3d_device);
}
