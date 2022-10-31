#include "FrameSizer.h"

FrameSizer::FrameSizer()
	: Ui(false)
	, dragging_(false)
	, prev_drag_pos_(Vector2{})
	, on_drag_handler_{}
{
}

FrameSizer::~FrameSizer()
{
	
}

void FrameSizer::Update()
{
	Ui::Update();

	//�巡�װ� �Ͼ ������ InvokeDrag(�巡�� �̵���)
	if (dragging_) {
		InvokeDrag(GET_MOUSE_POS() - prev_drag_pos_);
		prev_drag_pos_ = GET_MOUSE_POS();
	}

	if (KEY_UP(KEY::LBUTTON)) {
		dragging_ = false;
	}

	ChildrenUpdate();
}

void FrameSizer::LbuttonDown()
{
	dragging_ = true;
	prev_drag_pos_ = GET_MOUSE_POS();

}

void FrameSizer::InvokeDrag(Vector2 delta)
{
	on_drag_handler_.handler(on_drag_handler_.frame, delta);
}
