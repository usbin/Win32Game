#include "Director_Scene_01.h"
#include "PathManager.h"
#include "FileManager.h"
#include "Spawner.h"

Director_Scene_01::Director_Scene_01()
{
}

Director_Scene_01::~Director_Scene_01()
{
}

void Director_Scene_01::Update()
{
	if (KEY_DOWN(KEY::F11)) {
		ChangeScene(SCENE_TYPE::SCENE_TOOL);
	}

    if (KEY_DOWN(KEY::R)) {
        TCHAR file_path[256] = _T("");
        TCHAR initial_path[256];
        _tcscpy_s(initial_path, (PathManager::GetInstance()->GetContentPath()).c_str());


        OPENFILENAME ofn = {};
        memset(&ofn, 0, sizeof(OPENFILENAME));
        ofn.lStructSize = sizeof(OPENFILENAME);
        ofn.hwndOwner = Core::GetInstance()->get_main_hwnd();
        ofn.lpstrFilter = _T("Map File\0*.map\0");
        ofn.lpstrFile = file_path;
        ofn.nMaxFile = 256;
        ofn.lpstrInitialDir = initial_path;


        if (GetOpenFileName(&ofn)) {
            FileManager::GetInstance()->LoadMap(file_path);
        }
    }
    if (KEY_DOWN(KEY::S)) {
        Spawner::GetInstance()->RandomSpawn(TILE_OBJECT_TYPE::WOOD, Vector2{ 0, 0 }, Vector2{ 600, 600 }, 5);
    }
}
