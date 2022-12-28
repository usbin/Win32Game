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

void DrawRectangle(ID3D11Device* p_d3d_device, const Vector2& base_pos, const Vector2& scale, ARGB line_color)
{

	ID3D11DeviceContext* p_immediate_context;
	p_d3d_device->GetImmediateContext(&p_immediate_context);

	//점 좌표
	const int vertice_count = 4;
	CustomVertex vertices[] =
	{
		{ XMFLOAT3(base_pos.x,				base_pos.y,				0.f), XMFLOAT2(0, 0)},
		{ XMFLOAT3(base_pos.x + scale.x,	base_pos.y,				0.f), XMFLOAT2(1, 0)},
		{ XMFLOAT3(base_pos.x + scale.x,	base_pos.y + scale.y,	0.f), XMFLOAT2(1, 1)},
		{ XMFLOAT3(base_pos.x,				base_pos.y + scale.y,	0.f), XMFLOAT2(0, 1)}
	};
	//선 인덱스
	const int line_indices_count = 8;
	UINT line_indices[] = {
		0, 1, 1, 2, 2, 3, 3, 0
	};

	//==========================
	// 선 그리기
	//==========================
	//Vertex Buffer 채우기
	DXClass::GetInstance()->WriteVertexBuffer(vertices, vertice_count);
	//Line Index Buffer 채우기
	DXClass::GetInstance()->WriteIndexBuffer(line_indices, line_indices_count);
	//Constant Buffer 채우기
	DXClass::GetInstance()->WriteConstantBufferOnRender(FALSE, ARGB_TO_XMFLOAT(line_color));
	// Set primitive topology
	p_immediate_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	p_immediate_context->DrawIndexed(line_indices_count, 0, 0);


	p_immediate_context->Release();
}

void DrawRectangle(ID3D11Device* p_d3d_device, const Vector2& base_pos, const Vector2& scale, ARGB line_color, ARGB plane_color)
{
	//면->선 순서로 그림.
	ID3D11DeviceContext* p_immediate_context;
	p_d3d_device->GetImmediateContext(&p_immediate_context);

	//점 좌표
	const int vertice_count = 4;
	CustomVertex vertices[] =
	{
		{ XMFLOAT3(base_pos.x,				base_pos.y,				0.f), XMFLOAT2(0, 0)},
		{ XMFLOAT3(base_pos.x + scale.x,	base_pos.y,				0.f), XMFLOAT2(1, 0)},
		{ XMFLOAT3(base_pos.x + scale.x,	base_pos.y + scale.y,	0.f), XMFLOAT2(1, 1)},
		{ XMFLOAT3(base_pos.x,				base_pos.y + scale.y,	0.f), XMFLOAT2(0, 1)}
	};
	//선 인덱스
	const int line_indices_count = 8;
	UINT line_indices[] = {
		0, 1, 1, 2, 2, 3, 3, 0
	};
	//면 인덱스
	const int plane_indices_count = 6;
	UINT plane_indices[] = {
		0, 1, 2, 2, 3, 0
	};

	//=======================
	// 면 그리기
	//=======================
	//Vertex Buffer 채우기
	DXClass::GetInstance()->WriteVertexBuffer(vertices, vertice_count);
	//Plane Index Buffer 채우기
	DXClass::GetInstance()->WriteIndexBuffer(plane_indices, plane_indices_count);
	//Constant Buffer 채우기
	DXClass::GetInstance()->WriteConstantBufferOnRender(FALSE, ARGB_TO_XMFLOAT(plane_color));
	// Set primitive topology
	p_immediate_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	p_immediate_context->DrawIndexed(plane_indices_count, 0, 0);

	//==========================
	// 선 그리기
	//==========================
	// Vertex 색깔 변경(line_color)
	for (int i = 0; i < vertice_count; i++) {
		//vertices[i].color = ARGB_TO_XMFLOAT(line_color);
	}
	//Vertex Buffer 채우기
	DXClass::GetInstance()->WriteVertexBuffer(vertices, vertice_count);
	// Indices 변경(line index)
	DXClass::GetInstance()->WriteIndexBuffer(line_indices, line_indices_count);
	//Constant Buffer 채우기
	DXClass::GetInstance()->WriteConstantBufferOnRender(FALSE, ARGB_TO_XMFLOAT(line_color));
	// Set primitive topology
	p_immediate_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	p_immediate_context->DrawIndexed(line_indices_count, 0, 0);


	p_immediate_context->Release();

}

void DrawTexture(ID3D11Device* p_d3d_device, const Vector2& base_pos, const Vector2& scale, const Vector2& texture_base_pos, const Vector2& texture_scale, Texture* texture)
{
	ID3D11DeviceContext* p_immediate_context;
	p_d3d_device->GetImmediateContext(&p_immediate_context);

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

	// Set primitive topology
	p_immediate_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	p_immediate_context->DrawIndexed(plane_indices_count, 0, 0);

	p_immediate_context->Release();
}

void DrawFixedsizeText(ID3D11Device* p_d3d_device, const Vector2& base_pos, const Vector2& scale, const TCHAR* text, UINT text_length, tstring font_name, UINT font_size, D2D1::ColorF font_color, DWRITE_FONT_STYLE font_style, DWRITE_FONT_WEIGHT font_weight, DWRITE_TEXT_ALIGNMENT text_alighment, DWRITE_PARAGRAPH_ALIGNMENT paragraph_alignment)
{
	DXClass::GetInstance()->SetTextFormat(font_name, _T("ko-kr"), font_size, font_style, font_weight, text_alighment, paragraph_alignment);
	DXClass::GetInstance()->RenderText(text, text_length, base_pos, scale, font_color);
}

void DrawAutosizeText(ID3D11Device* p_d3d_device, const Vector2& base_pos, const Vector2& scale, const TCHAR* text, UINT text_length, tstring font_name, D2D1::ColorF font_color, DWRITE_FONT_STYLE font_style, DWRITE_FONT_WEIGHT font_weight, DWRITE_TEXT_ALIGNMENT text_alighment, DWRITE_PARAGRAPH_ALIGNMENT paragraph_alignment, UINT max_font_size, UINT min_font_size, UINT max_lines)
{
	UINT font_size = min_font_size;
	//\n의 개수 + 1개가 라인 수
	UINT line = 1;
	for (int i = 0; i < text_length; i++) {
		if (text[i] == '\n') line++;
	}
	//CASE 1 : 그리려는 영역이 필요로 하는 영역보다 클 경우 -> 폰트 사이즈 키움
	if (scale.x > font_size * text_length && scale.y > font_size*line) {
		font_size = min(min(scale.x/text_length, scale.y), max_font_size);
	}
	//CASE 2 : 그리려는 영역이 필요로 하는 영역보다 작을 경우 -> 폰트 사이즈 줄임
	//			(1) min font 까지 줄이고,
	//			(2) 그래도 부족하면 줄바꿈.
	else if (scale.x < font_size * text_length || scale.y < font_size*line) {
		font_size = max(min(scale.x/text_length, scale.y), min_font_size);
		
	}

	DXClass::GetInstance()->SetTextFormat(font_name, _T("ko-kr"), font_size, font_style, font_weight, text_alighment, paragraph_alignment);
	DXClass::GetInstance()->RenderText(text, text_length, base_pos, scale, font_color);
}
