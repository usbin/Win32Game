#pragma once
#include "Scene.h"

class TileObject;
class Scene_Farm : public Scene
{
private:
	std::vector<TileObject*> tile_objects_;
	bool initialized_ = false;
public:
	Scene_Farm(ID3D11Device* p_d3d_device) : Scene(p_d3d_device) {};
	virtual ~Scene_Farm() override {};
	virtual bool Enter(SCENE_TYPE from) override;
	virtual bool Exit() override;

	void Initialize();
	void Reinitialize(SCENE_TYPE from);
	void CreateUis(Player* player);
};

