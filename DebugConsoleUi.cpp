#include "DebugConsoleUi.h"
#include "InputUi.h"
#include "ButtonUi.h"
#include "Decorator.h"
#include "Spawner.h"
#include "Time.h"
void DebugConsoleUi::Init()
{
	//1. 자식 항목 만들기
	InputUi* input_ui = DEBUG_NEW InputUi(true);
	OnInputEnterArgs args;
	args.sender = this;
	input_ui->Init(this, [](tstring text, OnInputEnterArgs args) {
		DebugConsoleUi* owner = reinterpret_cast<DebugConsoleUi*>(args.sender);
		if (owner) {
			owner->OnInput(text);
		}
	}, args);
	input_ui->set_is_selectable(true);
	input_ui->set_group_type(GROUP_TYPE::UI);
	input_ui->set_pos(Vector2{ 20.f, get_scale().y-60.f});
	input_ui->set_scale(Vector2{ get_scale().x - 30.f, 40.f });
	input_ui->set_parent(this);
	AddChild(input_ui);
	input_ui->set_hint(_T("Type command"));
	UiManager::GetInstance()->SelectTarget(input_ui);
	
	log_offset_ = Vector2{ 25.f, get_scale().y - 60.f };
	log_scale_ = Vector2{ input_ui->get_scale().x, 16.f };
	//Ui* log_ui = DEBUG_NEW Ui(true);
	//log_ui->set_pos(Vector2{ 10, 30 });
	//log_ui->set_scale(input_ui->get_pos() + Vector2{ 0.f, input_ui->get_scale().y + 2.f });
	//log_ui->set_parent(this);
	//AddChild(log_ui);

}

void DebugConsoleUi::Update()
{
	Ui::Update();


}

void DebugConsoleUi::Render(ID3D11Device* p_d3d_device)
{


	Decorator::GetInstance()->GetConsoleFrame()->Render(p_d3d_device, this, RENDER_LAYER::TOP);
	for (int i = 0; i < log_.size(); i++) {
		DrawFixedsizeText(p_d3d_device, get_final_pos() + log_offset_ + Vector2{0.f, -((int)log_.size() - i)*log_scale_.y}, log_scale_
			, log_[i].c_str(), log_[i].size() + 1, _T("둥근모꼴"), log_scale_.y
			, D2D1::ColorF::White, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT_CENTER, RENDER_LAYER::TOP);
	}
	

	ChildrenRender(p_d3d_device);
	
}

//input에서 enter가 들어왔을 때
void DebugConsoleUi::OnInput(tstring text)
{
	
	//명령 처리
	tstringstream iss(text);
	std::vector<tstring> commands;
	for (int i = 0; i < 10; i++) {
		commands.push_back(_T(""));
	}
	tstring str;
	int i = 0;
	while (iss >> str && i<10) {
		commands[i++] = str;
	}
	Excute(commands);



}

void DebugConsoleUi::PrintConsole(tstring text)
{
	log_.push_back(text);
	if (log_.size() > 30) {
		log_.pop_front();
	}
}

void DebugConsoleUi::Excute(std::vector<tstring>& commands)
{

	//스폰
	if (commands[0] == _T("SPAWN")) {
		//$ SPAWN => 랜덤 나무 스폰
		Spawner::GetInstance()->RandomSpawn(TILE_OBJECT_TYPE::WOOD, Vector2{ 0, 0 }, Vector2{ 600, 600 }, 5);
		PrintConsole(_T("(0, 0) ~ (600, 600) 랜덤 나무 소환"));
	}
	//시간 관련
	if (commands[0] == _T("TIME")) {
		//$ TIME => 인게임 시간 출력
		if (commands[1].empty()) {
			int s = Game::GetInstance()->get_day_uptime_s();
			TCHAR buffer[30];
			_stprintf_s(buffer, _T("%d일차 %02d시 %02d분 %02d초"), Game::GetInstance()->get_day(), s / 60 / 60, s / 60 % 60, s % 60);
			PrintConsole(buffer);
		}
	}
}
