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
	//�ڽ� �׸� �����
	Game::GetInstance()->StartGame();
}

void TimerUi::Update()
{
	Ui::Update();


	//�ΰ��� 30��=1800��(=���� 30��)�� ����ϸ� UI ����
	if (TO_INGAME_TIME(Game::GetInstance()->get_uptime_s()) >= 1800) {
		//�ؽ�Ʈ ����� ��� ã�ƾ���.
	}


	ChildrenUpdate();
}

void TimerUi::Render(ID3D11Device* p_d3d_device)
{
	Ui::Render(p_d3d_device);

	ChildrenRender(p_d3d_device);
}
