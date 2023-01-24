#include "AskSleepUi.h"
#include "Game.h"
#include "AskSleepBtn.h"
#include "Decorator.h"
AskSleepUi::AskSleepUi(bool is_static_pos) : Ui(is_static_pos)
{
	Game::GetInstance()->ControlFreeze();
	Game::GetInstance()->TimeFreeze();
}

AskSleepUi::~AskSleepUi()
{
	Game::GetInstance()->ControlUnfreeze();
	Game::GetInstance()->TimeUnfreeze();
}

void AskSleepUi::Init()
{
	//�ڽ� Ui�� �����
	AskSleepBtn* yes_btn = DEBUG_NEW AskSleepBtn(true);
	yes_btn->set_pos(Vector2{ 10.f, get_scale().y/2.f });
	yes_btn->set_scale(Vector2{ get_scale().x/2.f-15.f, 30.f });
	yes_btn->set_parent(this);
	yes_btn->set_group_type(GROUP_TYPE::UI);
	yes_btn->Init(_T("��"));
	yes_btn->AddOnClickHandler([](DWORD_PTR param1, DWORD_PTR param2) {
		AskSleepUi* ui = reinterpret_cast<AskSleepUi*>(param1);
		DeleteGObject(ui, GROUP_TYPE::UI);
		Game::GetInstance()->ShowDayFinishUi();
		}, reinterpret_cast<DWORD_PTR>(this), 0);
	AddChild(yes_btn);
	btns_[CURSOR_YES] = yes_btn;

	//�ڽ� Ui�� �����
	AskSleepBtn* no_btn = DEBUG_NEW AskSleepBtn(true);
	no_btn->set_pos(Vector2{ get_scale().x/2.f+10.f, get_scale().y / 2.f });
	no_btn->set_scale(Vector2{ get_scale().x/2.f-15.f, 30.f });
	no_btn->set_parent(this);
	no_btn->set_group_type(GROUP_TYPE::UI);
	no_btn->Init(_T("�ƴϿ�"));
	no_btn->AddOnClickHandler([](DWORD_PTR param1, DWORD_PTR param2) {
		AskSleepUi* ui = reinterpret_cast<AskSleepUi*>(param1);
		DeleteGObject(ui, GROUP_TYPE::UI);
		}, reinterpret_cast<DWORD_PTR>( this), 0);
	AddChild(no_btn);
	btns_[CURSOR_NO] = no_btn;

	cursor_ = CURSOR_NO;
	no_btn->set_cursored(true);
}

void AskSleepUi::Update()
{
	Ui::Update();
	if (KEY_DOWN(KEY::A)) {
		cursor_ = CURSOR_YES;
		btns_[CURSOR_YES]->set_cursored(true);
		btns_[CURSOR_NO]->set_cursored(false);
		
	}
	if (KEY_DOWN(KEY::D)) {
		cursor_ = CURSOR_NO;
		btns_[CURSOR_YES]->set_cursored(false);
		btns_[CURSOR_NO]->set_cursored(true);
	}
	if (KEY_DOWN(KEY::ENTER)) {
		btns_[cursor_]->LbuttonClick();
		
	}
}

void AskSleepUi::Render(ID3D11Device* p_d3d_device)
{

	Decorator::GetInstance()->GetSimpleFrame()->Render(p_d3d_device, this, RENDER_LAYER::PLAYER);

	tstring text(_T("���� �߱��?"));
	DrawFixedsizeText(p_d3d_device, get_final_pos(), Vector2{ get_scale().x, 50.f }
		, text.c_str(), text.size() + 1, _T("�ձٸ��"), 20
		, D2D1::ColorF::Black, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_WEIGHT_NORMAL
		, DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER
		, RENDER_LAYER::PLAYER);

	ChildrenRender(p_d3d_device);
}
