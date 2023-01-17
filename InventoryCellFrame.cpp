#include "InventoryCellFrame.h"

void InventoryCellFrame::Render(ID3D11Device* p_d3d_device, Ui* ui, RENDER_LAYER layer)
{
	Vector2 pos = ui->get_final_pos();
	Vector2 scale = ui->get_scale();

	float line_width = 3.f; //�׸���, ���ݻ� �β�
	//���� ���
	DrawRectangle(p_d3d_device, pos, scale, ARGB(0xFFFFCB7B), 0, ARGB(0xFFFFCB7B), layer);
	//�׸���(��, �� 2px)
	DrawRectangle(p_d3d_device, pos, Vector2{ scale.x, line_width}, ARGB(0x33000000), line_width, layer);
	DrawRectangle(p_d3d_device, pos + Vector2{ scale.x - line_width, line_width }, Vector2{ line_width, scale.y-line_width }, ARGB(0x33000000), line_width, layer);
	//���ݻ�(��, �� 2px)
	DrawRectangle(p_d3d_device, pos + Vector2{ 0.f, scale.y - line_width }, Vector2{ scale.x, line_width }, ARGB(0x33FFFFFF), line_width, layer);
	DrawRectangle(p_d3d_device, pos, Vector2{ line_width, scale.y }, ARGB(0x33FFFFFF), line_width, layer);

}
