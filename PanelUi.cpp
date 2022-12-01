#include "PanelUi.h"

PanelUi::PanelUi()
	: Ui(true)
	, prev_drag_pos_{}
	, dragging_(false)
	, draggable_(true)
{
}

PanelUi::~PanelUi()
{
}



void PanelUi::Update()
{
	Ui::Update();

	ChildrenUpdate();
}

void PanelUi::FinalUpdate()
{
	Ui::FinalUpdate();

	//마우스 LBUTTON이 떨어졌다면 dragging도 끝난 것.
	if (!KEY_HOLD(KEY::LBUTTON)) {
		dragging_ = false;
	}

	//드래그에 따라 위치 이동
	if (dragging_&&draggable_) {
		Vector2 diff = GET_MOUSE_POS() - prev_drag_pos_;
		set_pos(get_pos() + diff);
		prev_drag_pos_ = GET_MOUSE_POS();
	}

	ChildrenFinalUpdate();
}

void PanelUi::Render(ID3D11Device* p_d3d_device)
{
	Ui::Render(p_d3d_device);


	Vector2 pos = get_final_pos();
	Vector2 scale = get_scale();

	if (!is_static_pos()) pos = WorldToRenderPos(pos);

	if (dragging_) {
		DrawRectangle(p_d3d_device, pos, scale, ARGB(0xff00ff00), ARGB(0xffffffff));

	}
	else {
		DrawRectangle(p_d3d_device, pos, scale, ARGB(0xff000000), ARGB(0xffffffff));
	}

	ChildrenRender(p_d3d_device);

}

void PanelUi::MouseOn()
{
}

void PanelUi::LbuttonClick()
{
}

void PanelUi::LbuttonDown()
{
	//패널 안에서 마우스 누르면 드래그 시작
	prev_drag_pos_ = GET_MOUSE_POS();
	dragging_ = true;

}

void PanelUi::LbuttonUp()
{
}
