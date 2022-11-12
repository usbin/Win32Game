#include "ButtonUi.h"
#include "Texture.h"
#include "Sprite.h"

ButtonUi::ButtonUi(bool is_static_pos)
	: Ui(is_static_pos)
	, on_click_handler{}
	, is_selected_(false)
{
}

ButtonUi::~ButtonUi()
{
}

void ButtonUi::Render(LPDIRECT3DDEVICE9 p_d3d_device)
{
	Ui::Render(p_d3d_device);


	Vector2 pos = get_final_pos();
	Vector2 scale = get_scale();

	if (!is_static_pos()) pos = WorldToRenderPos(pos);
	if (is_selected_) {
		DrawRectangle(p_d3d_device, pos, scale, 0xff0000ff, 0xffffffff);
	}
	if (get_lbutton_hold()) {
		if (get_sprite()) {
			/*Sprite* sprite = get_sprite();
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
				, RGB(255, 0, 255));*/
		}
		else {
			DrawRectangle(p_d3d_device, pos, scale, 0xffff0000, 0xffffffff);
		}
	}
	else {
		if (get_sprite()) {
			/*Sprite* sprite = get_sprite();
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
				, RGB(255, 0, 255));*/
		}
		else {
			DrawRectangle(p_d3d_device, pos, scale, 0xff000000, 0xffffffff);
		}
	}

	ChildrenRender(p_d3d_device);
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
