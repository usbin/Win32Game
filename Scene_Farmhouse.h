#pragma once
#include "global.h"
#include "Scene.h"
class Scene_Farmhouse : public Scene
{
private:
	bool initialized_ = false;
public:

	Scene_Farmhouse(ID3D11Device* p_d3d_device) : Scene(p_d3d_device) {};
	// Scene을(를) 통해 상속됨
	virtual bool Enter(SCENE_TYPE from) override;
	virtual bool Exit() override;

	void Initialize();
	void Reinitialize();
	void CreateUis(Player* player);
};

