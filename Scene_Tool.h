#pragma once
#include "Scene.h"
class Texture;
class Director_Scene_Tool;

//타일맵 수정하는 화면
class Scene_Tool : public Scene
{
public:
	Scene_Tool();
	Scene_Tool(ID3D11Device* p_d3d_device);
	~Scene_Tool();

private:
	HDC hdc_ = 0;

	UINT column_count_ = 0;
	UINT row_count_ = 0;
	Director_Scene_Tool* director_ = nullptr;

	Texture* tileuis_texture_ = nullptr;
	Vector2 texture_base_pos_ = Vector2::Zero();
	Vector2 texture_scale_ = Vector2::Zero();
	Vector2 sprite_scale_ = Vector2::Zero();
	Vector2 interval_ = Vector2::Zero();
	int count_ = 0;
public:
	virtual bool Enter() override;
	virtual bool Exit() override;

	void CreateEmptyTilemap(UINT column_count, UINT row_count);
	void ChangeTileuisTexture(Texture* tileuis_texture, Vector2 texture_base_pos, Vector2 texture_scale, Vector2 sprite_scale, Vector2 interval, int count);

	Tile* GetTile(Vector2 world_pos); //해당 위치에 있는 타일 리턴. 없으면 nullptr
	inline UINT get_column_count() { return column_count_; };
	inline UINT get_row_count() { return row_count_; };
	inline Director_Scene_Tool* get_director() { return director_; };
	inline Texture* get_tileuis_texture() {
		return tileuis_texture_;
	}
	inline Vector2 get_texture_base_pos() { return texture_base_pos_; };
	inline Vector2 get_texture_scale() { return texture_scale_; };
	inline Vector2 get_sprite_scale() { return sprite_scale_; };
	inline Vector2 get_interval() { return interval_; };
	inline int get_count() { return count_; };

};