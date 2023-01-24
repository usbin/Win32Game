#include "DayFinishedDetailBtn.h"
#include "Decorator.h"
void DayFinishedDetailBtn::Init()
{
}

void DayFinishedDetailBtn::Render(ID3D11Device* p_d3d_device)
{
	if (get_enabled()) {
		Decorator::GetInstance()->GetSimpleFrame()->Render(p_d3d_device, this, RENDER_LAYER::TOP);

	}
}
