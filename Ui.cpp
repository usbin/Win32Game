#include "Ui.h"
#include "Core.h"
#include "Sprite.h"
#include "Texture.h"

Ui::Ui(bool is_static_pos)
	: is_static_pos_(is_static_pos)
	, mouse_on_check_(false)
	, lbutton_hold_(false)
	, parent_(nullptr)
	, final_pos_{}
	, enabled_(true)
	, selectable_(false)
	, is_selected_(false)
{
}

Ui::~Ui()
{
	SafeDeleteVector<Ui*>(children_);
}



void Ui::Update()
{
	if (enabled_) {
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(Core::GetInstance()->get_main_hwnd(), &pt);
		Vector2 mouse_pos{ pt };
		Vector2 pos = get_final_pos();
		Vector2 scale = get_scale();
		//화면 안에서 마우스 이벤트가 일어났을 경우만
		if (Vector2{ 0, 0 } <= mouse_pos && mouse_pos <= Core::GetInstance()->get_resolution()) {
			//mouse 좌표는 항상 화면을 기준으로 한 render 좌표이므로 world 좌표로 변환해줌.
			mouse_pos = RenderToWorldPos(mouse_pos);
			//pos는 이 ui가 static pos를 사용하지 않을 경우에만 world 좌표로 변환해줌.
			if (is_static_pos_) pos = RenderToWorldPos(pos);
			mouse_on_check_ = (pos <= mouse_pos && mouse_pos <= pos + scale);

		}
		else {
			mouse_on_check_ = false;
		}
	}
	else {
		mouse_on_check_ = false;
	}

	ChildrenUpdate();
}

void Ui::FinalUpdate()
{
	final_pos_ = get_pos();
	//자식일 경우: 부모의 0,0을 기준으로 한 상대좌표임.
	if (get_parent() != nullptr) {
		final_pos_ += get_parent()->get_final_pos();
	}

	ChildrenFinalUpdate();
}

void Ui::Render(LPDIRECT3DDEVICE9 p_d3d_device)
{
	/*if (enabled_) {
		Sprite* sprite = get_sprite();
		Vector2 pos = get_final_pos();
		if (!is_static_pos()) pos = WorldToRenderPos(pos);
		const Vector2& scale = get_scale();
		if (sprite != nullptr) {
			Texture* texture = sprite->get_texture();
			const Vector2& sprite_base_pos = sprite->get_base_pos();
			const Vector2& sprite_scale = sprite->get_scale();
			TransparentBlt(hdc
				, static_cast<int>(pos.x)
				, static_cast<int>(pos.y)
				, static_cast<int>(scale.x)
				, static_cast<int>(scale.y)
				, texture->get_hdc()
				, static_cast<int>(sprite_base_pos.x)
				, static_cast<int>(sprite_base_pos.y)
				, static_cast<int>(sprite_scale.x)
				, static_cast<int>(sprite_scale.y)
				, RGB(255, 0, 255));
		}
	}*/
	

	ChildrenRender(p_d3d_device);
}


//=============================================================
//
//		자식 Ui 클래스에서 Update, FinalUpdate, Render 후에
//		실행시켜줘야 하는 함수들.
//
//=============================================================
void Ui::ChildrenUpdate()
{
	for (auto iter = children_.begin(); iter != children_.end(); iter++) {
		(*iter)->Update();
	}
}

void Ui::ChildrenFinalUpdate()
{
	for (auto iter = children_.begin(); iter != children_.end(); iter++) {
		(*iter)->FinalUpdate();
	}
}


void Ui::ChildrenRender(LPDIRECT3DDEVICE9 p_d3d_device)
{
	for (auto iter = children_.begin(); iter != children_.end(); iter++) {
		(*iter)->Render(p_d3d_device);
	}
}