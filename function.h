#pragma once
#include "global.h"

class GObject;
class Texture;
float DtF();

void CreateGObject(GObject* object, GROUP_TYPE type);
void DeleteGObject(GObject* object, GROUP_TYPE type);
void ChangeScene(SCENE_TYPE scene_type);

Vector2 WorldToRenderPos(Vector2 world_pos); // ������ǥ -> ī�޶� ���� �����ǥ�� ��ȯ
Vector2 RenderToWorldPos(Vector2 render_pos); // ī�޶� ���� �����ǥ -> ������ǥ�� ��ȯ


//====================
// �׸��� �Լ�
//====================
void DrawRectangle(ID3D11Device* p_d3d_device, const Vector2& base_pos, const Vector2& scale, ARGB line_color);
void DrawRectangle(ID3D11Device* p_d3d_device, const Vector2& base_pos, const Vector2& scale, ARGB line_color, ARGB plane_color);
void DrawTexture(ID3D11Device* p_d3d_device, const Vector2& base_pos, const Vector2& scale, const Vector2& texture_base_pos, const Vector2& texture_scale, Texture* texture);

template <typename T>
void SafeDeleteVector(std::vector<T>& cont) {
	for (auto item : cont) {
		delete item;
	}
	cont.clear();
}

template <typename T1, typename T2>
void SafeDeleteMap(std::map<T1, T2>& map) {
	for (auto pair : map) {
		delete pair.second;
	}
	map.clear();
}
