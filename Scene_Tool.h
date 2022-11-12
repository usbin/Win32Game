#pragma once
#include "Scene.h"

//타일맵 수정하는 화면
class Scene_Tool : public Scene
{
public:
	Scene_Tool();
	Scene_Tool(LPDIRECT3DDEVICE9 p_d3d_device);
	~Scene_Tool();

private:
	HDC hdc_;

public:
	virtual bool Enter() override;
	virtual bool Exit() override;

	
};