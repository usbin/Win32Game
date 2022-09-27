#include "PanelUi.h"

PanelUi::PanelUi()
	: Ui(true)
	, prev_drag_pos_{}
	, dragging_(false)
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

	//���콺 LBUTTON�� �������ٸ� dragging�� ���� ��.
	if (!KEY_HOLD(KEY::LBUTTON)) {
		dragging_ = false;
	}

	//�巡�׿� ���� ��ġ �̵�
	if (dragging_) {
		Vector2 diff = GET_MOUSE_POS() - prev_drag_pos_;
		set_pos(get_pos() + diff);
		prev_drag_pos_ = GET_MOUSE_POS();
	}

	ChildrenFinalUpdate();
}

void PanelUi::Render(HDC hdc)
{
	Vector2 pos = get_final_pos();
	Vector2 scale = get_scale();

	if (!is_static_pos()) pos = WorldToRenderPos(pos);

	if (get_lbutton_hold()) {
		SelectGdi _(hdc, PEN_TYPE::GREEN);
		Rectangle(hdc, pos.x, pos.y, pos.x + scale.x, pos.y + scale.y);

	}
	else {
		Rectangle(hdc, pos.x, pos.y, pos.x + scale.x, pos.y + scale.y);
	}

	ChildrenRender(hdc);
}

void PanelUi::MouseOn()
{
}

void PanelUi::MouseClick()
{
}

void PanelUi::MouseDown()
{
	//�г� �ȿ��� ���콺 ������ �巡�� ����
	prev_drag_pos_ = GET_MOUSE_POS();
	dragging_ = true;

}

void PanelUi::MouseUp()
{
}
