#include "Director_Scene_Title.h"
#include "SceneManager.h"
#include "FileManager.h"
#include "Core.h"
#include "PathManager.h"
#include "Background_Title.h"
#include "TitleText_Title.h"
Director_Scene_Title::Director_Scene_Title()
{
}

Director_Scene_Title::~Director_Scene_Title()
{
}

void Director_Scene_Title::Init(Background_Title* bg, TitleText_Title* title)
{
    bg_ = bg;
    title_ = title;
}

void Director_Scene_Title::Update()
{
    if (bg_ && bg_->IsAnimationDone() && 
        title_ && !title_->IsAnimationDone()) {
        Vector2 resolution = Core::GetInstance()->get_resolution();
        title_->set_dest_pos(Vector2(resolution.x / 2.f - title_->get_scale().x / 2.f, resolution.y / 4.f));
        title_->set_duration(3);
    }


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
