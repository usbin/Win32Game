#pragma once
#include "Scene.h"

class TileObject;
class Scene_01 : public Scene
{
private:
	std::vector<TileObject*> tile_objects_;
public:
	Scene_01(ID3D11Device* p_d3d_device) : Scene(p_d3d_device) {};
	virtual ~Scene_01() override {};
	virtual bool Enter() override;
	virtual bool Exit() override;
};

