#include "DayFinishedDetailImgUi.h"
#include "Decorator.h"
void DayFinishedDetailImgUi::Init()
{
}

void DayFinishedDetailImgUi::Render(ID3D11Device* p_d3d_device)
{
	Decorator::GetInstance()->GetSimpleFrame()->Render(p_d3d_device, this, RENDER_LAYER::PLAYER);
}
