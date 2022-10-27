#pragma once
#include "global.h"
#include "RealObject.h"


class TileEditUi;
class ButtonUi;
class TileUi;
class TileCell;
class Director_Scene_Tool : public RealObject
{
public:
	Director_Scene_Tool();
	~Director_Scene_Tool();
private:
	TileEditUi* tile_edit_ui_;

public:
	virtual void Update();

};

