#include "Ui.h"
#include "Core.h"
#include "Sprite.h"
#include "Texture.h"
#include "Animator.h"
#include "UiManager.h"

Ui::Ui(bool is_static_pos)
	: is_static_pos_(is_static_pos)
	, mouse_on_check_(false)
	, lbutton_hold_(false)
	, parent_(nullptr)
	, final_pos_{}
	, enabled_(true)
	, selectable_(false)
	, is_selected_(false)
	, animator_ (nullptr)
{
}

Ui::~Ui()
{
	if (animator_) delete animator_;
	SafeDeleteVector<Ui*>(children_);

	if (UiManager::GetInstance()->get_selected_target() == this) {
		UiManager::GetInstance()->ResetSelection();
	}

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
		//ȭ�� �ȿ��� ���콺 �̺�Ʈ�� �Ͼ�� ��츸
		if (Vector2{ 0, 0 } <= mouse_pos && mouse_pos <= Core::GetInstance()->get_resolution()) {
			//mouse ��ǥ�� �׻� ȭ���� �������� �� render ��ǥ�̹Ƿ� world ��ǥ�� ��ȯ����.
			mouse_pos = RenderToWorldPos(mouse_pos);
			//pos�� �� ui�� static pos�� ������� ���� ��쿡�� world ��ǥ�� ��ȯ����.
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
	if (enabled_) {

		if (animator_) animator_->Update();
		final_pos_ = get_pos();
		//�ڽ��� ���: �θ��� 0,0�� �������� �� �����ǥ��.
		if (get_parent() != nullptr) {
			final_pos_ += get_parent()->get_final_pos();
		}
	}
	

	ChildrenFinalUpdate();
}

void Ui::Render(ID3D11Device* p_d3d_device)
{
	if (enabled_ && get_visible()) {
		Vector2 pos = get_final_pos();
		if (!is_static_pos()) pos = WorldToRenderPos(pos);
		const Vector2& scale = get_scale();

		Sprite* sprite = get_sprite();
		if (animator_) {
			animator_->Render(p_d3d_device);
		}
		else if (sprite != nullptr) {
			Texture* texture = sprite->get_texture();
			const Vector2& sprite_base_pos = sprite->get_base_pos();
			const Vector2& sprite_scale = sprite->get_scale();
			DrawTexture(p_d3d_device, pos, scale, sprite_base_pos, sprite_scale, texture);
		}
	}
	

	ChildrenRender(p_d3d_device);
}


//=============================================================
//
//		�ڽ� Ui Ŭ�������� Update, FinalUpdate, Render �Ŀ�
//		���������� �ϴ� �Լ���.
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


void Ui::ChildrenRender(ID3D11Device* p_d3d_device)
{
	for (auto iter = children_.begin(); iter != children_.end(); iter++) {
		(*iter)->Render(p_d3d_device);
	}
}