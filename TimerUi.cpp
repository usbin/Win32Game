#include "TimerUi.h"
#include "ResManager.h"
#include "Sprite.h"
#include "Game.h"
#include "Core.h"
#include "Game.h"
TimerUi::TimerUi()
	: Ui(true)
{
	Texture* texture = ResManager::GetInstance()->LoadTexture(_T("Ingame Timer Ui Background"), _T("texture\\light-gray.png"));
	Sprite* sprite = new Sprite();
	sprite->QuickSet(texture, this, get_pos(), get_scale());
	ChangeSprite(sprite);
	//자식 항목 만들기
	Game::GetInstance()->StartGame();
}

void TimerUi::Update()
{
	Ui::Update();


	//인게임 30분=1800초(=현실 30초)가 경과하면 UI 갱신
	if (TO_INGAME_TIME(Game::GetInstance()->get_uptime_s()) >= 1800) {
		//텍스트 출력할 방법 찾아야함.
	}


	ChildrenUpdate();
}

void TimerUi::Render(ID3D11Device* p_d3d_device)
{
	Ui::Render(p_d3d_device);

	ChildrenRender(p_d3d_device);
}
