#pragma once
#include "Scene.h"


class Scene_Title : public Scene
{
public:
	Scene_Title(LPDIRECT3DDEVICE9 p_d3d_device) : Scene(p_d3d_device){};
	virtual ~Scene_Title() override {};
	virtual bool Enter() override;
	virtual bool Exit() override;
};

