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
	InvisibleWall* content_;

	bool dragging_;
	Vector2 prev_dragged_pos_;

	FrameSizer* left_top_sizer_;
	FrameSizer* right_top_sizer_;
	FrameSizer* left_bottom_sizer_;
	FrameSizer* right_bottom_sizer_;

	bool left_top_sizing_;
	bool right_top_sizing_;
	bool left_bottom_sizing_;
	bool right_bottom_sizing_;

public:
	virtual void Update() override;
	virtual void FinalUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Select() override;
	virtual void Unselect() override;
	virtual void LbuttonDown() override;

	inline InvisibleWall* get_content() { return content_; };
	inline void set_content(InvisibleWall* content) { content_ = content; };
};

