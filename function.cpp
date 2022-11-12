#include "function.h"
#include "GObject.h"
#include "EventManager.h"
#include "Time.h"
#include "Camera.h"

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

void DrawRectangle(LPDIRECT3DDEVICE9 p_d3d_device, const Vector2& base_pos, const Vector2& scale, DWORD line_color)
{
	//점 좌표
	CUSTOMVERTEX vertices[] = {
		{base_pos.x,			base_pos.y, 0.f, 1.0f, line_color},
		{base_pos.x + scale.x,	base_pos.y, 0.f, 1.0f, line_color},
		{base_pos.x + scale.x,	base_pos.y + scale.y, 0.f, 1.0f, line_color},
		{base_pos.x,			base_pos.y + scale.y, 0.f, 1.0f, line_color}
	};
	//선 인덱스
	WORD indices[] = {
		0, 1, 1, 2, 2, 3, 3, 0
	};

	//============
	//  점 셋팅
	//============
	//vertex buffer 생성
	IDirect3DVertexBuffer9* p_vb;
	if (FAILED(p_d3d_device->CreateVertexBuffer(sizeof(vertices),
		0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &p_vb, NULL))) {
		return;
	}

	//vertex 데이터의 범위를 잠그고, vertex buffer 포인터를 얻어옴.
	VOID* p_vertices;
	if (FAILED(p_vb->Lock(0, sizeof(vertices), (void**)&p_vertices, 0))) {
		return;
	}
	memcpy(p_vertices, vertices, sizeof(vertices));
	p_vb->Unlock();

	//============
	//  선 셋팅
	//============
	//index buffer 생성
	IDirect3DIndexBuffer9* p_ib;
	if (FAILED(p_d3d_device->CreateIndexBuffer(sizeof(indices),
		0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &p_ib, 0))) {
		return;
	}
	//index 데이터의 범위를 잠그고, 포인터를 얻어옴.
	VOID* p_indices;
	if (FAILED(p_ib->Lock(0, sizeof(indices), (void**)&p_indices, 0))) {
		return;
	}
	memcpy(p_indices, indices, sizeof(indices));
	p_ib->Unlock();

	//===============
	//  점, 선 그리기
	//===============
	p_d3d_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME); //선만 그리도록 설정
	p_d3d_device->SetStreamSource(0, p_vb, 0, sizeof(CUSTOMVERTEX));
	p_d3d_device->SetIndices(p_ib);
	p_d3d_device->SetFVF(D3DFVF_CUSTOMVERTEX);
	p_d3d_device->DrawIndexedPrimitive(D3DPT_LINELIST, 0, 0, 8, 0, 4);
}

void DrawRectangle(LPDIRECT3DDEVICE9 p_d3d_device, const Vector2& base_pos, const Vector2& scale, DWORD line_color, DWORD plane_color)
{
	//면->선 순서로 그림.
	
	// 점 좌표
	CUSTOMVERTEX vertices[] = {
		{base_pos.x,			base_pos.y, 0.f, 1.0f, plane_color},
		{base_pos.x + scale.x,	base_pos.y, 0.f, 1.0f, plane_color},
		{base_pos.x + scale.x,	base_pos.y + scale.y, 0.f, 1.0f, plane_color},
		{base_pos.x,			base_pos.y + scale.y, 0.f, 1.0f, plane_color}
	};
	// 선 인덱스
	WORD line_indices[] = {
		0, 1, 1, 2, 2, 3, 3, 0
	};
	// 면 인덱스
	WORD plane_indices[] = {
		0, 1, 2, 2, 3, 0
	};

	//============
	//  점 셋팅
	//============
	//vertex buffer 생성
	IDirect3DVertexBuffer9* p_vb;
	if (FAILED(p_d3d_device->CreateVertexBuffer(sizeof(vertices),
		0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &p_vb, NULL))) {
		return;
	}

	//vertex 데이터의 범위를 잠그고, vertex buffer 포인터를 얻어옴.
	VOID* p_vertices;
	if (FAILED(p_vb->Lock(0, sizeof(vertices), (void**)&p_vertices, 0))) {
		return;
	}
	memcpy(p_vertices, vertices, sizeof(vertices));
	p_vb->Unlock();

	//============
	//  면 셋팅
	//============
	//면 index buffer 생성
	IDirect3DIndexBuffer9* p_plane_ib;
	if (FAILED(p_d3d_device->CreateIndexBuffer(sizeof(plane_indices),
		0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &p_plane_ib, 0))) {
		return;
	}
	//면 index 데이터의 범위를 잠그고, 포인터를 얻어옴.
	VOID* p_plane_indices;
	if (FAILED(p_plane_ib->Lock(0, sizeof(plane_indices), (void**)&p_plane_indices, 0))) {
		return;
	}
	memcpy(p_plane_indices, plane_indices, sizeof(plane_indices));
	p_plane_ib->Unlock();

	//=============
	//  점+면 그리기
	//=============
	p_d3d_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID); //면을 그리도록 설정
	p_d3d_device->SetStreamSource(0, p_vb, 0, sizeof(CUSTOMVERTEX));
	p_d3d_device->SetIndices(p_plane_ib);
	p_d3d_device->SetFVF(D3DFVF_CUSTOMVERTEX);
	p_d3d_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

	//============
	//  점 셋팅
	//============
	//vertex 색깔을 선 색깔로 변경
	vertices[0].color = line_color;
	vertices[1].color = line_color;
	vertices[2].color = line_color;
	vertices[3].color = line_color;
	if (FAILED(p_vb->Lock(0, sizeof(vertices), (void**)&p_vertices, 0))) {
		return;
	}
	memcpy(p_vertices, vertices, sizeof(vertices));
	p_vb->Unlock();

	//============
	//  선 셋팅
	//============
	//선 index buffer 생성
	IDirect3DIndexBuffer9* p_line_ib;
	if (FAILED(p_d3d_device->CreateIndexBuffer(sizeof(line_indices),
		0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &p_line_ib, 0))) {
		return;
	}
	//선 index 데이터의 범위를 잠그고, 포인터를 얻어옴.
	VOID* p_line_indices;
	if (FAILED(p_line_ib->Lock(0, sizeof(line_indices), (void**)&p_line_indices, 0))) {
		return;
	}
	memcpy(p_line_indices, line_indices, sizeof(line_indices));
	p_line_ib->Unlock();


	//==============
	//  점+선 그리기
	//==============
	p_d3d_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME); //선만 그리도록 설정
	p_d3d_device->SetIndices(p_line_ib);
	p_d3d_device->DrawIndexedPrimitive(D3DPT_LINELIST, 0, 0, 8, 0, 4);
}
