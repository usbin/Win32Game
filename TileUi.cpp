#include "TileUi.h"
#include "SceneManager.h"
#include "TileEditUi.h"
#include "Sprite.h"
#include "Director_Scene_Tool.h"
#include "SceneManager.h"
#include "Tile.h"
TileUi::TileUi(bool is_static_pos)
	: ButtonUi(is_static_pos)
{
}

TileUi::~TileUi()
{
}

void TileUi::Update()
{
	Ui::Update();
	
	
	



	ChildrenUpdate();
}

void TileUi::Render(HDC hdc)
{
	Ui::Render(hdc);
	

	ChildrenRender(hdc);
}



void TileUi::IncreasePriority()
{
	//Tile ��Ͽ��� �ڷ� ������
	SceneManager::GetInstance()->get_current_scene()->ObjectToNext(GROUP_TYPE::UI, this);
}

void TileUi::DecreasePriority()
{
	//Tile ��Ͽ��� ������ ������
	SceneManager::GetInstance()->get_current_scene()->ObjectToPrev(GROUP_TYPE::UI, this);
}
