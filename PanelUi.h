#pragma once
#include "global.h"
#include "Ui.h"
class PanelUi : public Ui
{
public:
	PanelUi();
	~PanelUi();
private:

	Vector2 prev_drag_pos_ = Vector2::Zero();
	bool dragging_ = false;

	bool draggable_ = true;
public:
	virtual void Update() override;
	virtual void FinalUpdate() override;
	virtual void Render(ID3D11Device* p_d3d_device) override;

	virtual void MouseOn() override;
	virtual void LbuttonClick() override;
	virtual void LbuttonDown() override;
	virtual void LbuttonUp() override;
};

