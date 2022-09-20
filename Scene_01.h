#pragma once
#include "Scene.h"

class Scene_01 : public Scene
{
public:
	Scene_01(HDC hdc) : Scene(hdc) {};
	virtual ~Scene_01() override {};
	virtual bool Enter() override;
	virtual bool Exit() override;
};

