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

void PanelUi::Render(HDC hdc)
{
	Ui::Render(hdc);


	Vector2 pos = get_final_pos();
	Vector2 scale = get_scale();

	if (!is_static_pos()) pos = WorldToRenderPos(pos);

	if (dragging_) {
		SelectGdi _(hdc, PEN_TYPE::GREEN);
		Rectangle(hdc, static_cast<int>(pos.x), static_cast<int>(pos.y), static_cast<int>(pos.x + scale.x), static_cast<int>(pos.y + scale.y));

	}
	else {
		Rectangle(hdc, static_cast<int>(pos.x), static_cast<int>(pos.y), static_cast<int>(pos.x + scale.x), static_cast<int>(pos.y + scale.y));
	}

	ChildrenRender(hdc);

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
