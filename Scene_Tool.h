#pragma once
#include "Scene.h"

//Ÿ�ϸ� �����ϴ� ȭ��
class Scene_Tool : public Scene
{
public:
	Scene_Tool();
	Scene_Tool(HDC hdc);
	~Scene_Tool();

private:
	HDC hdc_;

public:
	virtual bool Enter() override;
	virtual bool Exit() override;

	
};