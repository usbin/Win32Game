#pragma once
#include "Ui.h"
class InvisibleWall;
class ImageUi;
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

	ImageUi* left_top_sizer_;
	ImageUi* right_top_sizer_;
	ImageUi* left_bottom_sizer_;
	ImageUi* right_bottom_sizer_;

	bool dragging_;
	Vector2 prev_dragged_pos_;

public:
	virtual void Update() override;
	virtual void FinalUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Select() override;
	virtual void Unselect() override;
	virtual void LbuttonDown() override;
	virtual void LbuttonUp() override;

	inline void set_content(InvisibleWall* content) { content_ = content; };
};

