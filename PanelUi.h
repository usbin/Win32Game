#pragma once
#include "global.h"
#include "Ui.h"
class PanelUi : public Ui
{
public:
	PanelUi();
	~PanelUi();
private:

	Vector2 prev_drag_pos_;
	bool dragging_;
public:
	virtual void Update() override;
	virtual void FinalUpdate() override;
	virtual void Render(HDC hdc) override;

	virtual void MouseOn() override;
	virtual void MouseClick() override;
	virtual void MouseDown() override;
	virtual void MouseUp() override;
};

