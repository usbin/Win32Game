#include "ConsoleFrame.h"

void ConsoleFrame::Render(ID3D11Device* p_d3d_device, Ui* ui, RENDER_LAYER layer)
{
	Vector2 pos = ui->get_final_pos();
	Vector2 scale = ui->get_scale();

	int width = 11;
	//내부 배경
	DrawRectangle(p_d3d_device, pos, scale, ARGB(0xFF000000), 0, ARGB(0xFF000000), layer);
	//그림자
	DrawRectangle(p_d3d_device, pos - 2, scale, ARGB(0x66000000), width + 3, layer);
	//가장 바깥쪽부터 테두리
	DrawRectangle(p_d3d_device, pos, scale, ARGB(0xFF893A08), 3, layer);
	DrawRectangle(p_d3d_device, pos + 3, scale - 3 * 2, ARGB(0xFFAB4B04), 3, layer);
	DrawRectangle(p_d3d_device, pos + 6, scale - 6 * 2, ARGB(0xFFE48409), 3, layer);
	DrawRectangle(p_d3d_device, pos + 9, scale - 9 * 2, ARGB(0xFF7C4121), 3, layer);
}
