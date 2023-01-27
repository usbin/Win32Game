#include "DayNightDarkness.h"
#include "Game.h"
#include "Core.h"
#include "DXClass.h"
#include "ResManager.h"
#include "Texture.h"
void DayNightDarkness::Init() {

	render_cmp_ = DEBUG_NEW RealObjectRenderComponent(this);
	Texture* darkness_texture = ResManager::GetInstance()->LoadTexture(_T("Darkness"), _T("texture\\Darkness.png"));
	RealObjectSprite* darkness_sprite = DEBUG_NEW RealObjectSprite();
	darkness_sprite->QuickSet(darkness_texture, this, Vector2{ 0, 0 }, darkness_texture->get_size());
	render_cmp_->ChangeSprite(darkness_sprite);
}
void DayNightDarkness::Update()
{
	float MAX_DARKNESS = 0.85;	//85%까지만 어두워짐.
	UINT hour = Game::GetInstance()->get_day_uptime_s()/60/60;
	UINT quarter_hour = Game::GetInstance()->get_day_uptime_s() / 60 / 15;
	if (hour >= 18 && hour<21) {	//18:00~21:00사이에 점점 어두워짐.
		opacity_ = min((((quarter_hour - 18*4.f) * 8.f) / 100) + 0.04, MAX_DARKNESS); //18시 정각에 4%로 시작. 15분마다 불투명도 8% 증가. 최대 85%를 넘지 않음.
	}
	//심야는 최대 어두움
	else if (hour >= 21 || (hour < 4)) {
		opacity_ = MAX_DARKNESS;
	}
	//4시부터 6시까지 점점 밝아짐
	else if (hour >= 4 && hour < 6) {
		opacity_ = 1-((quarter_hour - 3*4.f) * 12.f / 100);
	}
	else {
		opacity_ = 0.f;
	}
}

void DayNightDarkness::Render(ID3D11Device* p_d3d_device)
{
	//DrawTexture(p_d3d_device, get_pos(), Core::GetInstance()->get_resolution(), Vector2::Zero(), get_sprite()->get_scale(), get_sprite()->get_texture(), RENDER_LAYER::PLAYER);
	DrawRectangle(p_d3d_device, Vector2::Zero(), Core::GetInstance()->get_resolution(), ARGB(opacity_, 0, 0, 0), 1, ARGB(opacity_, 0, 0, 0), RENDER_LAYER::PLAYER);
	//DXClass::GetInstance()->SetLightMask(false);

}

