#include "Director_Scene_Farm.h"
#include "PathManager.h"
#include "FileManager.h"
#include "Core.h"

Director_Scene_Farm::Director_Scene_Farm()
{
}

Director_Scene_Farm::~Director_Scene_Farm()
{
}

void Director_Scene_Farm::Update()
{
    if (!CHECK_GAME_STATE(GAME_STATE_CONTROL_FREEZED)) {
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
    }
	
}
