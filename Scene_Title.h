#pragma once
#include "Scene.h"


class Scene_Title : public Scene
{
public:
	Scene_Title(HDC hdc) : Scene(hdc){};
	virtual ~Scene_Title() override {};
	virtual bool Enter() override;
	virtual bool Exit() override;
};

