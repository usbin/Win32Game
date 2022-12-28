#include "Director_Scene_Title.h"
#include "SceneManager.h"
#include "FileManager.h"
#include "Core.h"
#include "PathManager.h"
#include "Background_Title.h"
#include "TitleText_Title.h"
#include "NewGameBtn_Title.h"
Director_Scene_Title::Director_Scene_Title()
{
}

Director_Scene_Title::~Director_Scene_Title()
{
}

void Director_Scene_Title::Init(Background_Title* bg, TitleText_Title* title, NewGameBtn_Title* new_game_btn)
{
    bg_ = bg;
    title_ = title;
    new_game_btn_ = new_game_btn;
}

void Director_Scene_Title::Update()
{
    
    if (bg_ && bg_->IsAnimationDone()) {
        if (title_ && title_->get_effect_state() == EFFECT_STATE::PREVIOUS) {
            Vector2 resolution = Core::GetInstance()->get_resolution();
            title_->StartEffect(Vector2(resolution.x / 2.f - title_->get_scale().x / 2.f, resolution.y / 4.f), 1);
        }
        if (new_game_btn_ && new_game_btn_->get_effect_state() == EFFECT_STATE::PREVIOUS) {
            new_game_btn_->StartEffect();
            new_game_btn_->set_visible(true);
            new_game_btn_->set_enabled(true);
        }
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
