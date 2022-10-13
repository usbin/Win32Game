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

	//���콺 LBUTTON�� �������ٸ� dragging�� ���� ��.
	if (!KEY_HOLD(KEY::LBUTTON)) {
		dragging_ = false;
	}

	//�巡�׿� ���� ��ġ �̵�
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
	//�г� �ȿ��� ���콺 ������ �巡�� ����
	prev_drag_pos_ = GET_MOUSE_POS();
	dragging_ = true;

}

void PanelUi::LbuttonUp()
{
}
