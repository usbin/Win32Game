#pragma once
#include "Scene.h"

//타일맵 수정하는 화면
class Scene_Tool : public Scene
{
public:
	Scene_Tool();
	Scene_Tool(ID3D11Device* p_d3d_device);
	~Scene_Tool();

private:
	HDC hdc_;

	UINT column_count_;
	UINT row_count_;
public:
	virtual bool Enter() override;
	virtual bool Exit() override;

	void CreateEmptyTilemap(UINT column_count, UINT row_count);

	Tile* GetTile(Vector2 world_pos); //해당 위치에 있는 타일 리턴. 없으면 nullptr
	inline UINT get_column_count() { return column_count_; };
	inline UINT get_row_count() { return row_count_; };
};