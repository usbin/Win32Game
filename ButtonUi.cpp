#include "ButtonUi.h"
#include "Texture.h"
#include "Sprite.h"

ButtonUi::ButtonUi(bool is_static_pos)
	: Ui(is_static_pos)
	, on_click_handler{}
{
}

ButtonUi::~ButtonUi()
{
}

void ButtonUi::Render(HDC hdc)
{
	Ui::Render(hdc);


	Vector2 pos = get_final_pos();
	Vector2 scale = get_scale();

	if (!is_static_pos()) pos = WorldToRenderPos(pos);

	if (is_selected_) {
		SelectGdi __(hdc, PEN_TYPE::BLUE);
		Rectangle(hdc, static_cast<int>(pos.x), static_cast<int>(pos.y), static_cast<int>(pos.x + scale.x), static_cast<int>(pos.y + scale.y));
	}

	if (get_lbutton_hold()) {
		if (get_sprite()) {
			Sprite* sprite = get_sprite();
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
		else {
			SelectGdi _(hdc, PEN_TYPE::RED);
			Rectangle(hdc, static_cast<int>(pos.x), static_cast<int>(pos.y), static_cast<int>(pos.x + scale.x), static_cast<int>(pos.y + scale.y));
		}
	}
	else {
		if (get_sprite()) {
			Sprite* sprite = get_sprite();
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
		else {

			Rectangle(hdc, static_cast<int>(pos.x), static_cast<int>(pos.y), static_cast<int>(pos.x + scale.x), static_cast<int>(pos.y + scale.y));
		}
	}

	ChildrenRender(hdc);
}

void ButtonUi::MouseOn()
{
}

void ButtonUi::LbuttonClick()
{
	for (int i = 0; i < on_click_handler.size(); i++) {
		OnClickHandlerParams params = (on_click_handler[i]);
		params.on_click(params.param1, params.param2);
	}
}

void ButtonUi::LbuttonDown()
{

}

void ButtonUi::LbuttonUp()
{
}

void ButtonUi::AddOnClickHandler(OnClickHandler on_click, DWORD_PTR param1, DWORD_PTR param2)
{
	OnClickHandlerParams params{ on_click, param1, param2 };
	on_click_handler.push_back(params);
}
