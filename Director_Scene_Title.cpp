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
            title_->StartEffect(Vector2(resolution.x / 2.f - title_->get_scale().x / 2.f, resolution.y / 5.f), 1);
        }
        if (new_game_btn_ && new_game_btn_->get_effect_state() == EFFECT_STATE::PREVIOUS) {
            new_game_btn_->StartEffect();
            new_game_btn_->set_visible(true);
            new_game_btn_->set_enabled(true);
        }
    }

    if (KEY_DOWN(KEY::F2)) {
        ChangeScene(SCENE_TYPE::SCENE_01);
    }
	if (KEY_DOWN(KEY::F11)) {
		ChangeScene(SCENE_TYPE::SCENE_TOOL);
	}

    
}
