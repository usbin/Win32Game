#pragma once
#include "RealObject.h"
#include "global.h"
class Background_Title;
class TitleText_Title;
class NewGameBtn_Title;
class ExitBtn_Title;

class Director_Scene_Title : public RealObject
{
public:
	Director_Scene_Title();
	~Director_Scene_Title();
private:
	Background_Title* bg_ = nullptr;
	TitleText_Title* title_ = nullptr;
	NewGameBtn_Title* new_game_btn_ = nullptr;
	ExitBtn_Title* exit_btn_ = nullptr;
public:
	void Init(Background_Title* bg, TitleText_Title* title, NewGameBtn_Title* new_game_btn, ExitBtn_Title* exit_btn);
	virtual void Update() override;
};

