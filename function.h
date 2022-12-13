#pragma once
#include "global.h"

class GObject;
class Texture;
float DtF();

void CreateGObject(GObject* object, GROUP_TYPE type);
void DeleteGObject(GObject* object, GROUP_TYPE type);
void ChangeScene(SCENE_TYPE scene_type);

Vector2 WorldToRenderPos(Vector2 world_pos); // 월드좌표 -> 카메라 기준 상대좌표로 변환
Vector2 RenderToWorldPos(Vector2 render_pos); // 카메라 기준 상대좌표 -> 월드좌표로 변환


//====================
// 그리기 함수
//====================
void DrawRectangle(ID3D11Device* p_d3d_device, const Vector2& base_pos, const Vector2& scale, ARGB line_color);
void DrawRectangle(ID3D11Device* p_d3d_device, const Vector2& base_pos, const Vector2& scale, ARGB line_color, ARGB plane_color);
void DrawTexture(ID3D11Device* p_d3d_device, const Vector2& base_pos, const Vector2& scale, const Vector2& texture_base_pos, const Vector2& texture_scale, Texture* texture);
void DrawFixedsizeText(ID3D11Device* p_d3d_device, const Vector2& base_pos, const Vector2& scale, const TCHAR* text, UINT length, 
	tstring font_name, UINT font_size, D2D1::ColorF font_color, DWRITE_FONT_STYLE font_style, DWRITE_FONT_WEIGHT font_weight,
	DWRITE_TEXT_ALIGNMENT text_alighment, DWRITE_PARAGRAPH_ALIGNMENT paragraph_alignment);
void DrawAutosizeText(ID3D11Device* p_d3d_device, const Vector2& base_pos, const Vector2& scale, const TCHAR* text, UINT length,
	tstring font_name, D2D1::ColorF font_color, DWRITE_FONT_STYLE font_style, DWRITE_FONT_WEIGHT font_weight,
	DWRITE_TEXT_ALIGNMENT text_alighment, DWRITE_PARAGRAPH_ALIGNMENT paragraph_alignment,
	UINT max_font_size, UINT min_font_size, UINT max_lines);
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
