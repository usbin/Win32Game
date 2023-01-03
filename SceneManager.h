#pragma once
#include "global.h"
#include "Scene.h"

class Scene;


class SceneManager
{
	SINGLETON(SceneManager);
private:
	Scene* p_current_scene_ = nullptr;
	Scene* scenes_[static_cast<int>(SCENE_TYPE::END)];
	HDC hdc_ = 0;
	ID3D11Device* p_d3d_device_ = nullptr;
	bool ChangeScene(SCENE_TYPE type);
public:
	bool Init(ID3D11Device* p_d3d_device_);
	inline Scene* get_current_scene() { return p_current_scene_; };
	bool Update();
	bool Render(ID3D11Device* p_d3d_device_);
	void ClearView(ID3D11Device* p_d3d_device_);


	friend class EventManager;
};


