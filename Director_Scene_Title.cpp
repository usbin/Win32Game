#include "Director_Scene_Title.h"
#include "SceneManager.h"
Director_Scene_Title::Director_Scene_Title()
{
}

Director_Scene_Title::~Director_Scene_Title()
{
}

void Director_Scene_Title::Update()
{
	if (KEY_DOWN(KEY::TAB)) {
		ChangeScene(SCENE_TYPE::SCENE_TOOL);
	}
}
