#include "function.h"
#include "GObject.h"
#include "EventManager.h"
#include "Time.h"
#include "Camera.h"
#include "DXClass.h"
#include "Texture.h"
#include "DXClass.h"

void CreateGObject(GObject* object, GROUP_TYPE type) {
	Event eve = {};
	eve.type = EVENT_TYPE::CREATE_OBJECT;
	eve.param1 = (DWORD_PTR)object;
	eve.param2 = (DWORD_PTR)type;

	EventManager::GetInstance()->AddEvent(eve);
}

void DeleteGObject(GObject* object, GROUP_TYPE type) {
	Event eve = {};
	eve.type = EVENT_TYPE::DELETE_OBJECT;
	eve.param1 = (DWORD_PTR)object;
	eve.param2 = (DWORD_PTR)type;

	EventManager::GetInstance()->AddEvent(eve);
}

void ChangeScene(SCENE_TYPE scene_type)
{
	Event eve = {};
	eve.type = EVENT_TYPE::CHANGE_SCENE;
	eve.param1 = (DWORD_PTR)scene_type;

	EventManager::GetInstance()->AddEvent(eve);
}

float DtF()
{
	return static_cast<float>(Time::GetInstance()->dt_f());

}

Vector2 WorldToRenderPos(Vector2 static_pos)
{
	return Camera::GetInstance()->GetRenderPos(static_pos);
}

Vector2 RenderToWorldPos(Vector2 render_pos)
{
	return Camera::GetInstance()->GetWorldPos(render_pos);
}

void DrawRectangle(ID3D11Device* p_d3d_device, const Vector2& base_pos, const Vector2& scale, ARGB line_color, UINT width, RENDER_LAYER layer)
{

	ID3D11DeviceContext* p_immediate_context;
	p_immediate_context = DXClass::GetInstance()->get_immediate_context();

	//점 좌표
	CustomVertex vertices[] =
	{
		{ XMFLOAT3(base_pos.x,						base_pos.y,						0.f), XMFLOAT2(0,						0)},
		{ XMFLOAT3(base_pos.x + scale.x,			base_pos.y,						0.f), XMFLOAT2(1,						0)},
		{ XMFLOAT3(base_pos.x + scale.x,			base_pos.y + scale.y,			0.f), XMFLOAT2(1,						1)},
		{ XMFLOAT3(base_pos.x,						base_pos.y + scale.y,			0.f), XMFLOAT2(0,						1)},
		{ XMFLOAT3(base_pos.x + width,				base_pos.y,						0.f), XMFLOAT2(width/scale.x,			0)},
		{ XMFLOAT3(base_pos.x + scale.x - width,	base_pos.y,						0.f), XMFLOAT2(1-width/scale.x,			0)},
		{ XMFLOAT3(base_pos.x + scale.x,			base_pos.y + width,				0.f), XMFLOAT2(1,						width/scale.y)},
		{ XMFLOAT3(base_pos.x + scale.x,			base_pos.y + scale.y - width,	0.f), XMFLOAT2(1,						1-width/scale.y)},
		{ XMFLOAT3(base_pos.x + scale.x - width,	base_pos.y + scale.y,			0.f), XMFLOAT2(1 - width / scale.x,		1)},
		{ XMFLOAT3(base_pos.x + width,				base_pos.y + scale.y,			0.f), XMFLOAT2(width / scale.x,			1)},
		{ XMFLOAT3(base_pos.x,						base_pos.y + scale.y - width,	0.f), XMFLOAT2(0,						1 - width / scale.y)},
		{ XMFLOAT3(base_pos.x,						base_pos.y + width,				0.f), XMFLOAT2(0,						width / scale.y)},

	};
	//선 인덱스
	UINT line_indices[] = {
		0, 1, 6,
		6, 11, 0,
		1, 2, 8,
		8, 5, 1,
		2, 3, 10,
		10, 7, 2,
		3, 0, 4,
		4, 9, 3

	};

	//==========================
	// 선 그리기
	//==========================
	//Vertex Buffer 채우기
	DXClass::GetInstance()->WriteVertexBuffer(vertices, sizeof(vertices)/sizeof(CustomVertex));
	//Line Index Buffer 채우기
	DXClass::GetInstance()->WriteIndexBuffer(line_indices, sizeof(line_indices) / sizeof(UINT));
	//Constant Buffer 채우기
	DXClass::GetInstance()->WriteConstantBufferOnRender(FALSE, ARGB_TO_XMFLOAT(line_color));
	// Set primitive topology
	ID3D11RenderTargetView* layer_target_view = DXClass::GetInstance()->get_render_layer_target(layer);
	p_immediate_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	p_immediate_context->OMSetRenderTargets(1, &layer_target_view, NULL);
	p_immediate_context->DrawIndexed(sizeof(line_indices)/sizeof(UINT), 0, 0);


}

void DrawRectangle(ID3D11Device* p_d3d_device, const Vector2& base_pos, const Vector2& scale, ARGB line_color, UINT width, ARGB plane_color, RENDER_LAYER layer)
{
	//면->선 순서로 그림.
	ID3D11DeviceContext* p_immediate_context;
	p_immediate_context = DXClass::GetInstance()->get_immediate_context();

	//점 좌표
	CustomVertex vertices[] =
	{
		{ XMFLOAT3(base_pos.x,						base_pos.y,						0.f), XMFLOAT2(0,						0)},
		{ XMFLOAT3(base_pos.x + scale.x,			base_pos.y,						0.f), XMFLOAT2(1,						0)},
		{ XMFLOAT3(base_pos.x + scale.x,			base_pos.y + scale.y,			0.f), XMFLOAT2(1,						1)},
		{ XMFLOAT3(base_pos.x,						base_pos.y + scale.y,			0.f), XMFLOAT2(0,						1)},
		{ XMFLOAT3(base_pos.x + width,				base_pos.y,						0.f), XMFLOAT2(width / scale.x,			0)},
		{ XMFLOAT3(base_pos.x + scale.x - width,	base_pos.y,						0.f), XMFLOAT2(1 - width / scale.x,			0)},
		{ XMFLOAT3(base_pos.x + scale.x,			base_pos.y + width,				0.f), XMFLOAT2(1,						width / scale.y)},
		{ XMFLOAT3(base_pos.x + scale.x,			base_pos.y + scale.y - width,	0.f), XMFLOAT2(1,						1 - width / scale.y)},
		{ XMFLOAT3(base_pos.x + scale.x - width,	base_pos.y + scale.y,			0.f), XMFLOAT2(1 - width / scale.x,		1)},
		{ XMFLOAT3(base_pos.x + width,				base_pos.y + scale.y,			0.f), XMFLOAT2(width / scale.x,			1)},
		{ XMFLOAT3(base_pos.x,						base_pos.y + scale.y - width,	0.f), XMFLOAT2(0,						1 - width / scale.y)},
		{ XMFLOAT3(base_pos.x,						base_pos.y + width,				0.f), XMFLOAT2(0,						width / scale.y)},

	};
	//선 인덱스
	UINT line_indices[] = {
		0, 1, 6,
		6, 11, 0,
		1, 2, 8,
		8, 5, 1,
		2, 3, 10,
		10, 7, 2,
		3, 0, 4,
		4, 9, 3

	};
	//면 인덱스
	UINT plane_indices[] = {
		0, 1, 2, 2, 3, 0
	};

	//=======================
	// 면 그리기
	//=======================
	//Vertex Buffer 채우기
	DXClass::GetInstance()->WriteVertexBuffer(vertices, sizeof(vertices)/sizeof(CustomVertex));
	//Plane Index Buffer 채우기
	DXClass::GetInstance()->WriteIndexBuffer(plane_indices, sizeof(plane_indices)/sizeof(UINT));
	//Constant Buffer 채우기
	DXClass::GetInstance()->WriteConstantBufferOnRender(FALSE, ARGB_TO_XMFLOAT(plane_color));
	// Set primitive topology
	ID3D11RenderTargetView* layer_target_view = DXClass::GetInstance()->get_render_layer_target(layer);
	p_immediate_context->OMSetRenderTargets(1, &layer_target_view, NULL);
	p_immediate_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	p_immediate_context->DrawIndexed(sizeof(plane_indices) / sizeof(UINT), 0, 0);

	//==========================
	// 선 그리기
	//==========================
	//Vertex Buffer 채우기
	DXClass::GetInstance()->WriteVertexBuffer(vertices, sizeof(vertices) / sizeof(CustomVertex));
	// Indices 변경(line index)
	DXClass::GetInstance()->WriteIndexBuffer(line_indices, sizeof(line_indices)/sizeof(UINT));
	//Constant Buffer 채우기
	DXClass::GetInstance()->WriteConstantBufferOnRender(FALSE, ARGB_TO_XMFLOAT(line_color));
	// Set primitive topology
	p_immediate_context->DrawIndexed(sizeof(line_indices) / sizeof(UINT), 0, 0);


}

void DrawTexture(ID3D11Device* p_d3d_device, const Vector2& base_pos, const Vector2& scale
	, const Vector2& texture_base_pos, const Vector2& texture_scale, Texture* texture, RENDER_LAYER layer)
{
	ID3D11DeviceContext* p_immediate_context;
	p_immediate_context = DXClass::GetInstance()->get_immediate_context();

	ID3D11ShaderResourceView* p_resource_view = texture->get_resource_view();
	Vector2 r = texture->get_size();
	Vector2 normalized_texture_base_pos = texture_base_pos / r;
	Vector2 normalized_texture_scale = texture_scale / r;
		
	//점 좌표
	const int vertice_count = 4;
	CustomVertex vertices[] =
	{
		{ XMFLOAT3(base_pos.x,				base_pos.y,				0.f), XMFLOAT2(normalized_texture_base_pos.x, normalized_texture_base_pos.y)},
		{ XMFLOAT3(base_pos.x + scale.x,	base_pos.y,				0.f), XMFLOAT2(normalized_texture_base_pos.x + normalized_texture_scale.x, normalized_texture_base_pos.y)},
		{ XMFLOAT3(base_pos.x + scale.x,	base_pos.y + scale.y,	0.f), XMFLOAT2(normalized_texture_base_pos.x + normalized_texture_scale.x, normalized_texture_base_pos.y + normalized_texture_scale.y)},
		{ XMFLOAT3(base_pos.x,				base_pos.y + scale.y,	0.f), XMFLOAT2(normalized_texture_base_pos.x, normalized_texture_base_pos.y + normalized_texture_scale.y)}
	};
	//DX는 반드시 시계방향으로 그려야 함. scale이 음수면 좌우 반전이 된 것이므로 반시계방향으로 그려지게 됨. 따라서 시계방향으로 그려지도록 정점 순서 변경.
	if (scale.x < 0) {
		CustomVertex tmp = vertices[1];
		vertices[1] = vertices[3];
		vertices[3] = tmp;
	}
	
	//면 인덱스
	const int plane_indices_count = 6;
	UINT plane_indices[] = {
		0, 1, 2, 
		
		2, 3, 0
	};
	//Vertex Buffer 채우기
	DXClass::GetInstance()->WriteVertexBuffer(vertices, vertice_count);
	//Plane Index Buffer 채우기
	DXClass::GetInstance()->WriteIndexBuffer(plane_indices, plane_indices_count);
	//Constant Buffer 채우기
	DXClass::GetInstance()->WriteConstantBufferOnRender(TRUE, XMFLOAT4(0, 0, 0, 0));

	p_immediate_context->PSSetShaderResources(0, 1, &p_resource_view);
	ID3D11RenderTargetView* layer_target_view = DXClass::GetInstance()->get_render_layer_target(layer);
	p_immediate_context->OMSetRenderTargets(1, &layer_target_view, NULL);

	// Set primitive topology
	p_immediate_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	p_immediate_context->DrawIndexed(plane_indices_count, 0, 0);

}

void DrawFixedsizeText(ID3D11Device* p_d3d_device, const Vector2& base_pos, const Vector2& scale, const TCHAR* text, UINT text_length, tstring font_name, UINT font_size, D2D1::ColorF font_color, DWRITE_FONT_STYLE font_style, DWRITE_FONT_WEIGHT font_weight, DWRITE_TEXT_ALIGNMENT text_alighment, DWRITE_PARAGRAPH_ALIGNMENT paragraph_alignment, RENDER_LAYER layer)
{
	DXClass::GetInstance()->SetTextFormat(font_name, _T("ko-kr"), font_size, font_style, font_weight, text_alighment, paragraph_alignment);
	DXClass::GetInstance()->RenderText(text, text_length, base_pos, scale, font_color, layer);
}

void DrawAutosizeText(ID3D11Device* p_d3d_device, const Vector2& base_pos, const Vector2& scale, const TCHAR* text, UINT text_length, tstring font_name, D2D1::ColorF font_color, DWRITE_FONT_STYLE font_style, DWRITE_FONT_WEIGHT font_weight, DWRITE_TEXT_ALIGNMENT text_alighment, DWRITE_PARAGRAPH_ALIGNMENT paragraph_alignment, UINT max_font_size, UINT min_font_size, UINT max_lines, RENDER_LAYER layer)
{
	UINT font_size = min_font_size;
	float font_width_x = 0.6f;	//font의 가로 길이는 font size의 1/2만 차지함.
	//\n의 개수 + 1개가 라인 수
	UINT line = 1;
	for (int i = 0; i < text_length; i++) {
		if (text[i] == '\n') line++;
	}
	// 가로 scale/(글자수*0.5), 세로 scale 중 더 작은 값 선택
	font_size = min(scale.x / (text_length * font_width_x), scale.y);
	// 해당 값이 max보다 작고 min보다 큼을 보장.
	font_size = max(min(font_size, max_font_size), min_font_size);
	
	DXClass::GetInstance()->SetTextFormat(font_name, _T("ko-kr"), font_size, font_style, font_weight, text_alighment, paragraph_alignment);
	DXClass::GetInstance()->RenderText(text, text_length, base_pos, scale, font_color, layer);
}
