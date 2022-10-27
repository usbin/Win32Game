#include "InvisibleWallEditFrame.h"
#include "InvisibleWall.h"
#include "ImageUi.h"
#include "ResManager.h"
#include "Sprite.h"

InvisibleWallEditFrame::InvisibleWallEditFrame()
	: Ui(false)
	, content_(nullptr)
	, dragging_(false)
	, prev_dragged_pos_{ }
	, left_top_sizer_(nullptr)
	, right_top_sizer_(nullptr)
	, left_bottom_sizer_(nullptr)
	, right_bottom_sizer_(nullptr)
	
{
	
	//편집도구 생성

	/*Texture* texture = ResManager::GetInstance()->LoadTexture(_T("Sizer"), _T("texture\\circle_black_filled.bmp"));
	left_top_sizer_ = new ImageUi(false);
	left_top_sizer_->set_parent(this);
	this->AddChild(left_top_sizer_);
	left_top_sizer_->set_group_type(GROUP_TYPE::UI);
	left_top_sizer_->set_name(_T("Left Top Docker"));
	left_top_sizer_->set_scale(Vector2{ 10, 10 });
	left_top_sizer_->set_enabled(false);
	if (texture) {
		Sprite* sprite = new Sprite();
		sprite->QuickSet(texture, left_top_sizer_, 0, 0, 1, 1);
		left_top_sizer_->ChangeSprite(sprite);
	}

	right_top_sizer_ = new ImageUi(false);
	right_top_sizer_->set_parent(this);
	this->AddChild(right_top_sizer_);
	right_top_sizer_->set_group_type(GROUP_TYPE::UI);
	right_top_sizer_->set_name(_T("Right Top Docker"));
	right_top_sizer_->set_scale(Vector2{ 10, 10 });
	right_top_sizer_->set_enabled(false);
	if (texture) {
		Sprite* sprite = new Sprite();
		sprite->QuickSet(texture, right_top_sizer_, 0, 0, 1, 1);
		right_top_sizer_->ChangeSprite(sprite);
	}

	left_bottom_sizer_ = new ImageUi(false);
	left_bottom_sizer_->set_parent(this);
	this->AddChild(left_bottom_sizer_);
	left_bottom_sizer_->set_group_type(GROUP_TYPE::UI);
	left_bottom_sizer_->set_name(_T("Left Bottom Docker"));
	left_bottom_sizer_->set_scale(Vector2{ 10, 10 });
	left_bottom_sizer_->set_enabled(false);
	if (texture) {
		Sprite* sprite = new Sprite();
		sprite->QuickSet(texture, left_bottom_sizer_, 0, 0, 1, 1);
		left_bottom_sizer_->ChangeSprite(sprite);
	}

	right_bottom_sizer_ = new ImageUi(false);
	right_bottom_sizer_->set_parent(this);
	this->AddChild(right_bottom_sizer_);
	right_bottom_sizer_->set_group_type(GROUP_TYPE::UI);
	right_bottom_sizer_->set_name(_T("Right Bottom Docker"));
	right_bottom_sizer_->set_scale(Vector2{ 10, 10 });
	right_bottom_sizer_->set_enabled(false);
	if (texture) {
		Sprite* sprite = new Sprite();
		sprite->QuickSet(texture, right_bottom_sizer_, 0, 0, 1, 1);
		right_bottom_sizer_->ChangeSprite(sprite);
	}*/

}

InvisibleWallEditFrame::~InvisibleWallEditFrame()
{
}

void InvisibleWallEditFrame::Update()
{
	Ui::Update();

	////내용물이 없이 프레임만 있는 건 불가능하므로 스스로 삭제
	//if (!content_) {
	//	DeleteGObject(this, GROUP_TYPE::UI);
	//	return;
	//}


	////내용물의 위치 따라감.
	//set_pos(content_->get_pos());
	//set_scale(content_->get_scale());
	//left_top_sizer_->set_pos(Vector2{ -3, -3 });
	//right_top_sizer_->set_pos(Vector2{ get_scale().x - 3.f , -3.f });
	//left_bottom_sizer_->set_pos(Vector2{ -3.f , get_scale().y - 3.f });
	//right_bottom_sizer_->set_pos(Vector2{ get_scale().x - 3.f , get_scale().y - 3.f });

	////내용물의 클릭 여부를 탐지
	//// - 편집도구 드래그 처리
	//// - 드래그 이동 처리
	//if (KEY_UP(KEY::LBUTTON) && get_selected()) {
	//	dragging_ = false;
	//}
	//if (dragging_) {
	//	content_->set_pos(content_->get_pos() + (GET_MOUSE_POS() - prev_dragged_pos_));
	//	prev_dragged_pos_ = GET_MOUSE_POS();
	//}
	
	ChildrenUpdate();
}

void InvisibleWallEditFrame::FinalUpdate()
{
	Ui::FinalUpdate();

	ChildrenFinalUpdate();
}

void InvisibleWallEditFrame::Render(HDC hdc)
{

	Vector2 pos = WorldToRenderPos(get_final_pos());
	Vector2 scale = get_scale();
	if (get_selected()) {
		SelectGdi _(hdc, BRUSH_TYPE::BRIGHT_GRAY);
		Rectangle(hdc, pos.x, pos.y, pos.x + scale.x, pos.y + scale.y);
	}
	ChildrenRender(hdc);
}

void InvisibleWallEditFrame::Select()
{
	/*left_top_sizer_->set_enabled(true);
	right_top_sizer_->set_enabled(true);
	left_bottom_sizer_->set_enabled(true);
	right_bottom_sizer_->set_enabled(true);*/
}

void InvisibleWallEditFrame::Unselect()
{
	/*left_top_sizer_->set_enabled(false);
	right_top_sizer_->set_enabled(false);
	left_bottom_sizer_->set_enabled(false);
	right_bottom_sizer_->set_enabled(false);*/
}

void InvisibleWallEditFrame::LbuttonDown()
{
	if (get_selected()) {
		dragging_ = true;
		prev_dragged_pos_ = GET_MOUSE_POS();
	}
}

void InvisibleWallEditFrame::LbuttonUp()
{
}


