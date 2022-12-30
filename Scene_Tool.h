#pragma once
#include "Scene.h"

//Ÿ�ϸ� �����ϴ� ȭ��
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

	Tile* GetTile(Vector2 world_pos); //�ش� ��ġ�� �ִ� Ÿ�� ����. ������ nullptr
	inline UINT get_column_count() { return column_count_; };
	inline UINT get_row_count() { return row_count_; };
};