#include "HorizontalSplitFrame.h"
void HorizontalSplitFrame::Render(ID3D11Device* p_d3d_device, Ui* ui, RENDER_LAYER layer)
{
	
	Vector2 pos = ui->get_final_pos();
	Vector2 scale = ui->get_scale();

	int width = 11;
	//내부 배경
	DrawRectangle(p_d3d_device, pos, scale, ARGB(0xFFFFCB7B), 0, ARGB(0xFFFFCB7B), layer);
	//그림자
	DrawRectangle(p_d3d_device, pos-2, scale, ARGB(0x66000000), width + 3, layer);
	//가장 바깥쪽부터 테두리
	DrawRectangle(p_d3d_device, pos, scale, ARGB(0xFF893A08), 2, layer);
	DrawRectangle(p_d3d_device, pos+2, scale-2*2, ARGB(0xFFE48409), 3, layer);
	DrawRectangle(p_d3d_device, pos+5, scale-5*2, ARGB(0xFFAB4B04), 3, layer);
	DrawRectangle(p_d3d_device, pos+8, scale-8*2, ARGB(0xFF7C4121), 2, layer);
	//중앙선
	int border_width = 10;
	//그림자
	DrawRectangle(p_d3d_device, Vector2{ pos.x + width/2.f, pos.y + scale.y / 2.f - border_width/2.f-1.f}, Vector2{ scale.x - width, 2.f }, ARGB(0x66000000), border_width/2.f, layer);
	//가장 위부터 그리기
	DrawRectangle(p_d3d_device, Vector2{ pos.x+width/2.f, pos.y + scale.y / 2.f - border_width/2.f}, Vector2{scale.x-width, 2.f}, ARGB(0xFF893A08), 2, layer);
	DrawRectangle(p_d3d_device, Vector2{ pos.x+width/2.f, pos.y + scale.y / 2.f - border_width/2.f + 2.f}, Vector2{ scale.x - width, 3.f }, ARGB(0xFFE48409), 3, layer);
	DrawRectangle(p_d3d_device, Vector2{ pos.x + width / 2.f, pos.y + scale.y / 2.f - border_width / 2.f + 5.f }, Vector2{ scale.x - width, 3.f }, ARGB(0xFFAB4B04), 3, layer);
	DrawRectangle(p_d3d_device, Vector2{ pos.x + width / 2.f, pos.y + scale.y / 2.f - border_width / 2.f + 8.f }, Vector2{ scale.x - width, 2.f }, ARGB(0xFF7C4121), 2, layer);
}
