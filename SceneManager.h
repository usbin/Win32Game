#pragma once
#include "global.h"
#include "Scene.h"

class Scene;


class SceneManager
{
	SINGLETON(SceneManager);
private:
	Scene* p_current_scene_;
	Scene* scenes_[static_cast<int>(SCENE_TYPE::END)];
	HDC hdc_;
	bool ChangeScene(SCENE_TYPE type);
public:
	bool Init(HDC hdc);
	inline Scene* get_current_scene() { return p_current_scene_; };
	bool Update();
	bool Render(HDC hdc);
	void ClearView(HDC hdc);

	friend class EventManager;
};


