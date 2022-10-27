#pragma once
#include "Ui.h"
class InvisibleWall;
class ImageUi;
/// <summary>
/// InvisibleWall�� �׵θ��� �����Ǿ� Ŭ���Ǿ��� �� ũ�� ����, �̵� ���� ������ ó��
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

