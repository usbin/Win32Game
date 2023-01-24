#include "DayFinishedOkBtn.h"
#include "Decorator.h"
#include "UiSprite.h"
void DayFinishedOkBtn::Render(ID3D11Device* p_d3d_device)
{
	
	if (get_sprite()) {
		DrawTexture(p_d3d_device, get_final_pos(), get_scale(), get_sprite()->get_base_pos(), get_sprite()->get_scale(), get_sprite()->get_texture(), RENDER_LAYER::TOP);
	}
	ChildrenRender(p_d3d_device);
}
