#include "TimerUi.h"
#include "ResManager.h"
#include "UiSprite.h"
#include "Game.h"
#include "Core.h"
#include "Game.h"
TimerUi::TimerUi()
	: Ui(true)
{
	Texture* texture = ResManager::GetInstance()->LoadTexture(_T("Timer Ui Background"), _T("texture\\light-gray.png"));
	GObjectSprite* sprite = DEBUG_NEW UiSprite();
	sprite->QuickSet(texture, this, get_pos(), get_scale());
	ChangeSprite(sprite);
}

void TimerUi::Update()
{
	Ui::Update();


	//�ΰ��� 30��=1800��(=���� 30��)�� ����ϸ� UI ����
	if (TO_INGAME_TIME(Game::GetInstance()->get_day_uptime_s()) >= 1800) {
		//�ؽ�Ʈ ����� ��� ã�ƾ���.
	}


}

void TimerUi::Render(ID3D11Device* p_d3d_device)
{
	Ui::Render(p_d3d_device);

	UINT uptime_s = Game::GetInstance()->get_day_uptime_s();
	UINT hour = uptime_s / 60 / 60;
	UINT min = uptime_s % 60 - (uptime_s%60%15); //15�� �ֱ�� ����.
	
	Vector2 pos = is_static_pos() ? get_final_pos() : WorldToRenderPos(get_final_pos());
	Vector2 scale = get_scale();
	TCHAR buffer[64] = _T("");
	_stprintf_s(buffer, _T("%d����\n %02d:%02d"), Game::GetInstance()->get_day(), hour, min);

	DrawAutosizeText(p_d3d_device, pos, scale, buffer, _tcslen(buffer), _T("�ձٸ��"), D2D1::ColorF::Black
		, DWRITE_FONT_STYLE::DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_BOLD, DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_CENTER
		, DWRITE_PARAGRAPH_ALIGNMENT::DWRITE_PARAGRAPH_ALIGNMENT_CENTER, 30, 1, 1, RENDER_LAYER::TOP);

	ChildrenRender(p_d3d_device);
}
