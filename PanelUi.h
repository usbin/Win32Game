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

	bool draggable_;
public:
	virtual void Update() override;
	virtual void FinalUpdate() override;
	virtual void Render(LPDIRECT3DDEVICE9 p_d3d_device) override;

	virtual void MouseOn() override;
	virtual void LbuttonClick() override;
	virtual void LbuttonDown() override;
	virtual void LbuttonUp() override;
};

