#include "InvisibleWallEditFrame.h"
#include "InvisibleWall.h"
#include "ImageUi.h"
#include "ResManager.h"
#include "Sprite.h"
#include "Collider.h"
#include "FrameSizer.h"

InvisibleWallEditFrame::InvisibleWallEditFrame()
	: Ui(false)
	, content_(nullptr)
	, dragging_(false)
	, prev_dragged_pos_{ }
	, left_top_sizer_(nullptr)
	, right_top_sizer_(nullptr)
	, left_bottom_sizer_(nullptr)
	, right_bottom_sizer_(nullptr)
	, left_top_sizing_(false)
	, right_top_sizing_(false)
	, left_bottom_sizing_(false)
	, right_bottom_sizing_(false)
	
{
	
	//편집도구 생성

	Texture* texture = ResManager::GetInstance()->LoadTexture(_T("Sizer"), _T("texture\\circle_black_filled.bmp"));

	left_top_sizer_ = new FrameSizer();
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
	left_top_sizer_->SetOnDragListener([](InvisibleWallEditFrame* frame, Vector2 delta) {
		Vector2 content_pos = frame->get_content()->get_pos();
		Vector2 content_scale = frame->get_content()->get_scale();
		
		Vector2 content_scale_after = Vector2{ content_scale.x - delta.x, content_scale.y - delta.y };
		if (content_scale_after.x <= 10 || content_scale_after.y <= 10) {
			return;
		}
		frame->get_content()->set_scale(content_scale_after);
		frame->get_content()->set_pos((content_pos + content_scale / 2.f) - content_scale_after/2.f);
	}, this);

	right_top_sizer_ = new FrameSizer();
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
	right_top_sizer_->SetOnDragListener([](InvisibleWallEditFrame* frame, Vector2 delta) {
		Vector2 content_pos = frame->get_content()->get_pos();
		Vector2 content_scale = frame->get_content()->get_scale();

		Vector2 content_scale_after = Vector2{ content_scale.x + delta.x, content_scale.y - delta.y };
		if (content_scale_after.x <= 10 || content_scale_after.y <= 10) {
			return;
		}
		frame->get_content()->set_scale(Vector2{ content_scale_after.x, content_scale_after.y });
		frame->get_content()->set_pos(Vector2{ content_pos.x - content_scale.x/2.f +content_scale_after.x / 2.f, (content_pos.y+content_scale.y/2.f)-(content_scale_after.y/2.f)});
		}, this);

	left_bottom_sizer_ = new FrameSizer();
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
	left_bottom_sizer_->SetOnDragListener([](InvisibleWallEditFrame* frame, Vector2 delta) {
		Vector2 content_pos = frame->get_content()->get_pos();
		Vector2 content_scale = frame->get_content()->get_scale();

		Vector2 content_scale_after = Vector2{ content_scale.x - delta.x, content_scale.y + delta.y };
		if (content_scale_after.x <= 10 || content_scale_after.y <= 10) {
			return;
		}
		frame->get_content()->set_scale(Vector2{ content_scale_after.x, content_scale_after.y });
		frame->get_content()->set_pos(Vector2{ (content_pos.x + content_scale.x / 2.f) - (content_scale_after.x) / 2.f, content_pos.y-content_scale.y/2.f + content_scale_after.y / 2.f  });
		}, this);

	right_bottom_sizer_ = new FrameSizer();
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
	}
	right_bottom_sizer_->SetOnDragListener([](InvisibleWallEditFrame* frame, Vector2 delta) {
		Vector2 content_pos = frame->get_content()->get_pos();
		Vector2 content_scale = frame->get_content()->get_scale();

		Vector2 content_scale_after = Vector2{ content_scale.x + delta.x, content_scale.y + delta.y };
		if (content_scale_after.x <= 10 || content_scale_after.y <= 10) {
			return;
		}
		frame->get_content()->set_scale(Vector2{ content_scale_after.x, content_scale_after.y });
		frame->get_content()->set_pos(Vector2{ (content_pos.x - content_scale.x / 2.f) + (content_scale_after.x / 2.f), content_pos.y - content_scale.y / 2.f + content_scale_after.y / 2.f });
		}, this);

}

InvisibleWallEditFrame::~InvisibleWallEditFrame()
{
}

void InvisibleWallEditFrame::Update()
{
	Ui::Update();

	if (content_ == nullptr) {
		DeleteGObject(this, GROUP_TYPE::UI);
		return;
	}

	//내용물의 클릭 여부를 탐지
	// - 드래그 이동 처리
	// - 편집도구 드래그 처리
	if (dragging_) {
		content_->set_pos(content_->get_pos() + (GET_MOUSE_POS() - prev_dragged_pos_));
		prev_dragged_pos_ = GET_MOUSE_POS();
	}
	
	



	//내용물의 위치 따라감.
	set_pos(content_->get_pos() - content_->get_scale() / 2.f);
	set_scale(content_->get_scale());
	left_top_sizer_->set_pos(Vector2{ -3, -3 });
	right_top_sizer_->set_pos(Vector2{ -3.f + get_scale().x , -3.f });
	left_bottom_sizer_->set_pos(Vector2{ -3.f , get_scale().y - 3.f });
	right_bottom_sizer_->set_pos(Vector2{ get_scale().x - 3.f , get_scale().y - 3.f });

	if (KEY_UP(KEY::LBUTTON)) {
		dragging_ = false;
		left_top_sizing_ = false;
		right_top_sizing_ = false;
		left_bottom_sizing_ = false;
		right_bottom_sizing_ = false;

	}
	
	
	ChildrenUpdate();
}

void InvisibleWallEditFrame::FinalUpdate()
{
	Ui::FinalUpdate();

	
	ChildrenFinalUpdate();
}

void InvisibleWallEditFrame::Render(LPDIRECT3DDEVICE9 p_d3d_device)
{

	Vector2 pos = WorldToRenderPos(get_final_pos());
	Vector2 scale = get_scale();
	if (get_selected()) {
		/*SelectGdi _(hdc, BRUSH_TYPE::BRIGHT_GRAY);
		Rectangle(hdc, pos.x, pos.y, pos.x + scale.x, pos.y + scale.y);*/
	}
	ChildrenRender(p_d3d_device);
}

void InvisibleWallEditFrame::Select()
{
	left_top_sizer_->set_enabled(true);
	right_top_sizer_->set_enabled(true);
	left_bottom_sizer_->set_enabled(true);
	right_bottom_sizer_->set_enabled(true);
}

void InvisibleWallEditFrame::Unselect()
{
	left_top_sizer_->set_enabled(false);
	right_top_sizer_->set_enabled(false);
	left_bottom_sizer_->set_enabled(false);
	right_bottom_sizer_->set_enabled(false);
}

void InvisibleWallEditFrame::LbuttonDown()
{
	if (get_selected()) {
		dragging_ = true;
		prev_dragged_pos_ = GET_MOUSE_POS();
	}
}
