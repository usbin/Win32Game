#pragma once
#include "Scene.h"


class Scene_Title : public Scene
{
public:
	Scene_Title(ID3D11Device* p_d3d_device) : Scene(p_d3d_device){};
	virtual ~Scene_Title() override {};
	virtual bool Enter(SCENE_TYPE from) override;
	virtual bool Exit() override;
};

