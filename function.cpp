#include "function.h"
#include "GObject.h"
#include "EventManager.h"
#include "Time.h"
#include "Camera.h"
#include "DXClass.h"
#include "Texture.h"

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

	//�� ��ǥ
	const int vertice_count = 4;
	CustomVertex vertices[] =
	{
		{ XMFLOAT3(base_pos.x,				base_pos.y,				0.f), XMFLOAT2(0, 0)},
		{ XMFLOAT3(base_pos.x + scale.x,	base_pos.y,				0.f), XMFLOAT2(1, 0)},
		{ XMFLOAT3(base_pos.x + scale.x,	base_pos.y + scale.y,	0.f), XMFLOAT2(1, 1)},
		{ XMFLOAT3(base_pos.x,				base_pos.y + scale.y,	0.f), XMFLOAT2(0, 1)}
	};
	//�� �ε���
	const int line_indices_count = 8;
	UINT line_indices[] = {
		0, 1, 1, 2, 2, 3, 3, 0
	};

	//==========================
	// �� �׸���
	//==========================
	//Vertex Buffer ä���
	DXClass::GetInstance()->WriteVertexBuffer(vertices, vertice_count);
	//Line Index Buffer ä���
	DXClass::GetInstance()->WriteIndexBuffer(line_indices, line_indices_count);
	//Constant Buffer ä���
	DXClass::GetInstance()->WriteConstantBufferOnRender(FALSE, ARGB_TO_XMFLOAT(line_color));
	// Set primitive topology
	p_immediate_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	p_immediate_context->DrawIndexed(line_indices_count, 0, 0);


	p_immediate_context->Release();
}

void DrawRectangle(ID3D11Device* p_d3d_device, const Vector2& base_pos, const Vector2& scale, ARGB line_color, ARGB plane_color)
{
	//��->�� ������ �׸�.
	ID3D11DeviceContext* p_immediate_context;
	p_d3d_device->GetImmediateContext(&p_immediate_context);

	//�� ��ǥ
	const int vertice_count = 4;
	CustomVertex vertices[] =
	{
		{ XMFLOAT3(base_pos.x,				base_pos.y,				0.f), XMFLOAT2(0, 0)},
		{ XMFLOAT3(base_pos.x + scale.x,	base_pos.y,				0.f), XMFLOAT2(1, 0)},
		{ XMFLOAT3(base_pos.x + scale.x,	base_pos.y + scale.y,	0.f), XMFLOAT2(1, 1)},
		{ XMFLOAT3(base_pos.x,				base_pos.y + scale.y,	0.f), XMFLOAT2(0, 1)}
	};
	//�� �ε���
	const int line_indices_count = 8;
	UINT line_indices[] = {
		0, 1, 1, 2, 2, 3, 3, 0
	};
	//�� �ε���
	const int plane_indices_count = 6;
	UINT plane_indices[] = {
		0, 1, 2, 2, 3, 0
	};

	//=======================
	// �� �׸���
	//=======================
	//Vertex Buffer ä���
	DXClass::GetInstance()->WriteVertexBuffer(vertices, vertice_count);
	//Plane Index Buffer ä���
	DXClass::GetInstance()->WriteIndexBuffer(plane_indices, plane_indices_count);
	//Constant Buffer ä���
	DXClass::GetInstance()->WriteConstantBufferOnRender(FALSE, ARGB_TO_XMFLOAT(plane_color));
	// Set primitive topology
	p_immediate_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	p_immediate_context->DrawIndexed(plane_indices_count, 0, 0);

	//==========================
	// �� �׸���
	//==========================
	// Vertex ���� ����(line_color)
	for (int i = 0; i < vertice_count; i++) {
		//vertices[i].color = ARGB_TO_XMFLOAT(line_color);
	}
	//Vertex Buffer ä���
	DXClass::GetInstance()->WriteVertexBuffer(vertices, vertice_count);
	// Indices ����(line index)
	DXClass::GetInstance()->WriteIndexBuffer(line_indices, line_indices_count);
	//Constant Buffer ä���
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
		
	//�� ��ǥ
	const int vertice_count = 4;
	CustomVertex vertices[] =
	{
		{ XMFLOAT3(base_pos.x,				base_pos.y,				0.f), XMFLOAT2(normalized_texture_base_pos.x, normalized_texture_base_pos.y)},
		{ XMFLOAT3(base_pos.x + scale.x,	base_pos.y,				0.f), XMFLOAT2(normalized_texture_base_pos.x + normalized_texture_scale.x, normalized_texture_base_pos.y)},
		{ XMFLOAT3(base_pos.x + scale.x,	base_pos.y + scale.y,	0.f), XMFLOAT2(normalized_texture_base_pos.x + normalized_texture_scale.x, normalized_texture_base_pos.y + normalized_texture_scale.y)},
		{ XMFLOAT3(base_pos.x,				base_pos.y + scale.y,	0.f), XMFLOAT2(normalized_texture_base_pos.x, normalized_texture_base_pos.y + normalized_texture_scale.y)}
	};
	//�� �ε���
	const int plane_indices_count = 6;
	UINT plane_indices[] = {
		0, 1, 2, 
		
		2, 3, 0
	};
	//Vertex Buffer ä���
	DXClass::GetInstance()->WriteVertexBuffer(vertices, vertice_count);
	//Plane Index Buffer ä���
	DXClass::GetInstance()->WriteIndexBuffer(plane_indices, plane_indices_count);
	//Constant Buffer ä���
	DXClass::GetInstance()->WriteConstantBufferOnRender(TRUE, XMFLOAT4(0, 0, 0, 0));

	p_immediate_context->PSSetShaderResources(0, 1, &p_resource_view);

	// Set primitive topology
	p_immediate_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	p_immediate_context->DrawIndexed(plane_indices_count, 0, 0);

	p_immediate_context->Release();
}

