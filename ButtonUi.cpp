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

void ButtonUi::Render(ID3D11Device* p_d3d_device)
{
	Ui::Render(p_d3d_device);


	Vector2 pos = get_final_pos();
	Vector2 scale = get_scale();

	if (!is_static_pos()) pos = WorldToRenderPos(pos);

	if (get_lbutton_hold()) {
		if (get_sprite()) {

			Sprite* sprite = get_sprite();
			Texture* texture = sprite->get_texture();
			const Vector2& sprite_base_pos = sprite->get_base_pos();
			const Vector2& sprite_scale = sprite->get_scale();
			DrawTexture(p_d3d_device, pos, scale, sprite_base_pos, sprite_scale, texture);
		}
		else {
			DrawRectangle(p_d3d_device, pos, scale, ARGB(0xffff0000), ARGB(0xffffffff));
		}
	}
	else {
		if (get_sprite()) {
			Sprite* sprite = get_sprite();
			Texture* texture = sprite->get_texture();
			const Vector2& sprite_base_pos = sprite->get_base_pos();
			const Vector2& sprite_scale = sprite->get_scale();
			DrawTexture(p_d3d_device, pos, scale, sprite_base_pos, sprite_scale, texture);
		}
		else {
			DrawRectangle(p_d3d_device, pos, scale, ARGB(0xff000000), ARGB(0xffffffff));
		}
	}
	if (is_selected_) {
		DrawRectangle(p_d3d_device, pos, scale, ARGB(0xff0000ff));
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
