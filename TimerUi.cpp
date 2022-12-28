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
}

void TimerUi::Update()
{
	Ui::Update();


	//인게임 30분=1800초(=현실 30초)가 경과하면 UI 갱신
	if (TO_INGAME_TIME(Game::GetInstance()->get_day_uptime_s()) >= 1800) {
		//텍스트 출력할 방법 찾아야함.
	}


	ChildrenUpdate();
}

void TimerUi::Render(ID3D11Device* p_d3d_device)
{
	Ui::Render(p_d3d_device);

	UINT uptime_s = Game::GetInstance()->get_day_uptime_s();
	UINT hour = uptime_s / 60;
	UINT min = uptime_s % 60 - (uptime_s%60%15); //15분 주기로 저장.
	
	Vector2 pos = is_static_pos() ? get_final_pos() : WorldToRenderPos(get_final_pos());
	Vector2 scale = get_scale();
	tstring text = _T("");
	TCHAR day_buffer[10] = _T("");
	TCHAR hour_buffer[3] = _T("");
	TCHAR min_buffer[3] = _T("");
	_stprintf_s(day_buffer, _T("%d"), Game::GetInstance()->get_day());
	_stprintf_s(hour_buffer, _T("%d"), hour);
	_stprintf_s(min_buffer, _T("%d"), min);
	text.append(day_buffer);
	text.append(_T("일차\n"));
	text.append(hour_buffer);
	text.append(_T(":"));
	text.append(min_buffer);

	DrawAutosizeText(p_d3d_device, pos, scale, text.c_str(), _tcslen(text.c_str()), _T("둥근모꼴"), D2D1::ColorF::Black
		, DWRITE_FONT_STYLE::DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_BOLD, DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_CENTER
		, DWRITE_PARAGRAPH_ALIGNMENT::DWRITE_PARAGRAPH_ALIGNMENT_CENTER, 30, 1, 1);

	ChildrenRender(p_d3d_device);
}
