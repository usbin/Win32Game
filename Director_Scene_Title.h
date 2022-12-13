#pragma once
#include "RealObject.h"
#include "global.h"
class Background_Title;
class TitleText_Title;

class Director_Scene_Title : public RealObject
{
public:
	Director_Scene_Title();
	~Director_Scene_Title();
private:
	Background_Title* bg_;
	TitleText_Title* title_;
public:
	void Init(Background_Title* bg, TitleText_Title* title);
	virtual void Update() override;
};

