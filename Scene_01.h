#pragma once
#include "Scene.h"

class Scene_01 : public Scene
{
public:
	Scene_01(LPDIRECT3DDEVICE9 p_d3d_device) : Scene(p_d3d_device) {};
	virtual ~Scene_01() override {};
	virtual bool Enter() override;
	virtual bool Exit() override;
};

