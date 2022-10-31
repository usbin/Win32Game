#pragma once
#include "global.h"
#include "GObject.h"
#include "Ui.h"

class InvisibleWallEditFrame;

//드래그해서 변화량이 생길 때마다 리스너 호출
typedef void(*OnDragHandler)(InvisibleWallEditFrame* frame, Vector2 delta);
struct OnDragHandlerParams {
	OnDragHandler handler;
	InvisibleWallEditFrame* frame;
};
class FrameSizer : public Ui
{
public:
	FrameSizer();
	~FrameSizer();

private:
	//인자로 부모와 변화량 vector를 받음.
	OnDragHandlerParams on_drag_handler_;
	
	bool dragging_;
	Vector2 prev_drag_pos_;

public:
	virtual void Update() override;
	virtual void LbuttonDown() override;
	inline void SetOnDragListener(OnDragHandler handler, InvisibleWallEditFrame* frame) {
		on_drag_handler_ = OnDragHandlerParams{ handler, frame };
	}
	void InvokeDrag(Vector2 delta);
};

