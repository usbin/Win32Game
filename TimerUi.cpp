#include "TimerUi.h"
#include "ResManager.h"
#include "UiSprite.h"
#include "Core.h"
#include "Game.h"
#include "Player.h"
#include "Inventory.h"
TimerUi::TimerUi()
	: Ui(true)
{
	set_scale(Vector2{ 72*3, 59*3 });
	set_pos(Vector2{ Core::GetInstance()->get_resolution().x - get_scale().x, 0.f });

	Texture* texture = ResManager::GetInstance()->LoadTexture(_T("Timer Ui Background"), _T("texture\\StardewValley_Clock.png"));
	GObjectSprite* sprite = DEBUG_NEW UiSprite();
	sprite->QuickSet(texture, this, Vector2::Zero(), Vector2{72, 59});
	ChangeSprite(sprite);
}

void TimerUi::Init(Player* player)
{
	owner_ = player;
}

void TimerUi::Update()
{
	Ui::Update();

	if (owner_ && owner_->IsDead()) owner_ = nullptr;



}

void TimerUi::Render(ID3D11Device* p_d3d_device)
{
	Ui::Render(p_d3d_device);

	UINT uptime_s = Game::GetInstance()->get_day_uptime_s();
	UINT hour = uptime_s / 60/60;
	UINT min = uptime_s /60 % 60 - (uptime_s/60%60%15); //15분 주기로 저장.


	//날짜 출력
	Vector2 date_pos{ 85, 14 };
	Vector2 date_scale{ 110, 25 };
	TCHAR date_buffer[30] = _T("");
	tstring week;
	switch (Game::GetInstance()->get_day()%7) {
	case 0: week = _T("일"); break;
	case 1: week = _T("월"); break;
	case 2: week = _T("화"); break;
	case 3: week = _T("수"); break;
	case 4: week = _T("목"); break;
	case 5: week = _T("금"); break;
	case 6: week = _T("토"); break;
	}
	_stprintf_s(date_buffer, _T("%s, %d"), week.c_str(), Game::GetInstance()->get_day() % 28);
	DrawAutosizeText(p_d3d_device, get_final_pos()+date_pos,date_scale, date_buffer, _tcslen(date_buffer), _T("둥근모꼴"), D2D1::ColorF::Black
		, DWRITE_FONT_STYLE::DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_NORMAL, DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_CENTER
		, DWRITE_PARAGRAPH_ALIGNMENT::DWRITE_PARAGRAPH_ALIGNMENT_CENTER, 20, 1, 1, RENDER_LAYER::PLAYER);

	//시간 출력
	Vector2 clock_pos{ 85, 81};
	Vector2 clock_scale{119, 26};
	TCHAR clock_buffer[30] = _T("");
	tstring ampm;
	if (hour <= 12) {
		ampm = _T("오전");
	}
	else {
		ampm = _T("오후");
		hour -= 12;
	}
	_stprintf_s(clock_buffer, _T("%d:%02d %s"), hour, min, ampm.c_str());
	DrawAutosizeText(p_d3d_device, get_final_pos() + clock_pos, clock_scale, clock_buffer, _tcslen(clock_buffer), _T("둥근모꼴"), D2D1::ColorF::Black
		, DWRITE_FONT_STYLE::DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_NORMAL, DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_CENTER
		, DWRITE_PARAGRAPH_ALIGNMENT::DWRITE_PARAGRAPH_ALIGNMENT_CENTER, 20, 1, 1, RENDER_LAYER::PLAYER);



	//소지금 출력
	if (owner_ && owner_->get_inventory()) {
		Vector2 gold_pos{ 9, 142 };
		Vector2 gold_scale{ 185, 28 };
		TCHAR gold[30] = _T("");
		_stprintf_s(gold, _T("%d"), owner_->get_inventory()->GetGold());

		DrawFixedsizeText(p_d3d_device, get_final_pos() + gold_pos, gold_scale, gold, _tcslen(gold), _T("둥근모꼴"), 36, D2D1::ColorF(0x6B/256.f, 0x21/256.f, 0.f)
			, DWRITE_FONT_STYLE::DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_NORMAL, DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_TRAILING
			, DWRITE_PARAGRAPH_ALIGNMENT::DWRITE_PARAGRAPH_ALIGNMENT_CENTER, RENDER_LAYER::PLAYER);
	}

	ChildrenRender(p_d3d_device);
}
