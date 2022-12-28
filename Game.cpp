#include "Game.h"
Game::Game()
	: day_(1)
	, day_uptime_s_(0)
	, game_state_(GAME_STATE::FREEZED)
	, acc_dt_(0){};
Game::~Game() {};

void Game::StartGame()
{
	//���� ���ۿ� �ʿ��� ��� �ε�, ���� ���� ��
	acc_dt_ = 0.f;
	game_state_ = GAME_STATE::PLAYING;
}

void Game::Update()
{
	switch (game_state_) {
	case GAME_STATE::PLAYING:
	case GAME_STATE::PLAYER_FREEZED:
	{
		acc_dt_ += Time::GetInstance()->dt_f();
		if (acc_dt_ >= 1.) {
			day_uptime_s_++;
			acc_dt_ = 0.;
		}
	}
	}


}
