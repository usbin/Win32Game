#include "TileUi.h"
#include "SceneManager.h"
#include "TileEditUi.h"
#include "GObjectSprite.h"
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

void TileUi::Render(ID3D11Device* p_d3d_device)
{
	Ui::Render(p_d3d_device);
	

	ChildrenRender(p_d3d_device);
}



void TileUi::IncreasePriority()
{
	//Tile 목록에서 뒤로 보내기
	SceneManager::GetInstance()->get_current_scene()->ObjectToNext(GROUP_TYPE::UI, this);
}

void TileUi::DecreasePriority()
{
	//Tile 목록에서 앞으로 보내기
	SceneManager::GetInstance()->get_current_scene()->ObjectToPrev(GROUP_TYPE::UI, this);
}
