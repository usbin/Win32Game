#include "DebugConsoleUi.h"
#include "InputUi.h"
#include "ButtonUi.h"
#include "Decorator.h"
#include "Spawner.h"
#include "Time.h"
#include "Camera.h"
#include "SceneManager.h"
#include "Player.h"
#include "FieldTileObject.h"
#include "ItemDb.h"
#include "Seed.h"
#include "DayFinishedUi.h"
#include "Core.h"
#include "Inventory.h"

void DebugConsoleUi::Init()
{
	//1. �ڽ� �׸� �����
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
			, log_[i].c_str(), log_[i].size() + 1, _T("�ձٸ��"), log_scale_.y
			, D2D1::ColorF::White, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT_CENTER, RENDER_LAYER::TOP);
	}
	

	ChildrenRender(p_d3d_device);
	
}

//input���� enter�� ������ ��
void DebugConsoleUi::OnInput(tstring text)
{
	
	//��� ó��
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

	//����
	if (commands[0] == _T("SPAWN")) {
		if (commands[1] == _T("WOOD")) {
			//$ SPAWN WOOD=> ���� ���� ����
			Spawner::GetInstance()->RandomSpawn(TILE_OBJECT_TYPE::WOOD, Vector2{ 0, 0 }, Vector2{ 600, 600 }, 5);
			PrintConsole(_T("(0, 0) ~ (600, 600) ���� ���� ��ȯ"));

		}
		else if (commands[1] == _T("FIELD")) {
			if (commands[2] == _T("PARSNIP")) {
				//$ SPAWN FIELD PARSNIP => �� �ڶ� ���� �� ��ȯ

				Vector2 world_pos = GET_MOUSE_POS();
				Vector2 tile_pos;
				SceneManager::GetInstance()->get_current_scene()->GetTilePos(world_pos, tile_pos);
				FieldTileObject* parsnip = DEBUG_NEW FieldTileObject();
				parsnip->SetSeed(dynamic_cast<const Seed*>(ItemDb::GetInstance()->get_item((int)ITEM_CODE::PARSNIP_SEED)));
				parsnip->SetLevel(5);
				parsnip->set_pos(tile_pos);
				parsnip->set_scale(Vector2{ TILE_WIDTH, TILE_HEIGHT });
				parsnip->Init(TILE_OBJECT_TYPE::FIELD);
				CreateGObject(parsnip, GROUP_TYPE::TILE_OBJECT);
				PrintConsole(_T("���콺 ��ġ�� �� �ڶ� ���� �� ��ȯ��."));


			}

		}
			
	}
	//�ð� ����
	if (commands[0] == _T("TIME")) {
		//$ TIME => �ΰ��� �ð� ���
		if (commands[1].empty()) {
			int s = Game::GetInstance()->get_day_uptime_s();
			TCHAR buffer[30];
			_stprintf_s(buffer, _T("%d���� %02d�� %02d�� %02d��"), Game::GetInstance()->get_day(), s / 60 / 60, s / 60 % 60, s%60);
			PrintConsole(buffer);
		}
		else if (commands[1] == _T("FINISHDAY")) {
			Game::GetInstance()->FinishDayProcess();
			TCHAR buffer[30];
			_stprintf_s(buffer, _T("�������� �Ѿ."));
			PrintConsole(buffer);
		}
		else if (commands[1] != _T("0") && _ttoi(commands[1].c_str())!=0) {
			int hour = _ttoi(commands[1].c_str());
			Game::GetInstance()->SetTime(Game::GetInstance()->get_day(), hour, 0);

			TCHAR buffer[30];
			_stprintf_s(buffer, _T("%d�� %d������ ����"), hour, 0);
			PrintConsole(buffer);
		}
	}
	//�ΰ�����ǥ�� ������ִ� ��ɾ�
	if (commands[0] == _T("POSITION")) {
		//$ POSITION => ���콺 ��ġ ���
		if (commands[1] == _T("MOUSE")) {
			if (commands[2].empty()) {
				TCHAR buffer[100];
				Vector2 world_pos = GET_MOUSE_POS();
				Vector2 render_pos = WorldToRenderPos(world_pos);
				_stprintf_s(buffer, _T("[���콺 ��ġ] World (%.4f, %.4f), Render (%.4f, %.4f)"), world_pos.x, world_pos.y, render_pos.x, render_pos.y);
				PrintConsole(buffer);
			}
		}
	}
	// �������� �κ��丮�� �߰�
	if (commands[0] == _T("ITEM")) {
		if (commands[1] != _T("")) {
			int item_code = _ttoi(commands[1].c_str());
			int amount = 1;
			if (commands[2] != _T("")) {
				amount = _ttoi(commands[2].c_str());
			}
			const IItem* item = ItemDb::GetInstance()->get_item(item_code);
			if (item) {
				const std::vector<GObject*>& gobjs_player = SceneManager::GetInstance()->get_current_scene()->GetGroupObjects(GROUP_TYPE::PLAYER);
				if (!gobjs_player.empty()) {
					Player* player = dynamic_cast<Player*>(gobjs_player[0]);
					player->get_inventory()->AddItem(item, amount);
					TCHAR buffer[100];
					_stprintf_s(buffer, _T("�������ڵ� %d (%s) %d�� �κ��丮�� �߰���."), item_code, item->get_item_name().c_str(), amount);
					PrintConsole(buffer);
				}
			}
		}


	}
	if (commands[0] == _T("TEST")) {
		Game::GetInstance()->ShowDayFinishUi();
		
	}
}
