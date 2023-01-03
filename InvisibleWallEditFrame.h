#pragma once
#include "Ui.h"
class InvisibleWall;
class FrameSizer;
/// <summary>
/// InvisibleWall의 테두리에 부착되어 클릭되었을 때 크기 조정, 이동 등의 동작을 처리
/// </summary>
class InvisibleWallEditFrame : public Ui
{
public:
	InvisibleWallEditFrame();
	~InvisibleWallEditFrame();

private:
	InvisibleWall* content_ = nullptr;

	bool dragging_ = false;
	Vector2 prev_dragged_pos_ = Vector2::Zero();

	FrameSizer* left_top_sizer_ = nullptr;
	FrameSizer* right_top_sizer_ = nullptr;
	FrameSizer* left_bottom_sizer_ = nullptr;
	FrameSizer* right_bottom_sizer_ = nullptr;

	bool left_top_sizing_ = false;
	bool right_top_sizing_ = false;
	bool left_bottom_sizing_ = false;
	bool right_bottom_sizing_ = false;

public:
	virtual void Update() override;
	virtual void FinalUpdate() override;
	virtual void Render(ID3D11Device* p_d3d_device) override;
	virtual void Select() override;
	virtual void Unselect() override;
	virtual void LbuttonDown() override;

	inline InvisibleWall* get_content() { return content_; };
	inline void set_content(InvisibleWall* content) { content_ = content; };
};

