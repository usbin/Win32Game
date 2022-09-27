#include "Ui.h"
#include "Core.h"
Ui::Ui(bool is_static_pos)
	: is_static_pos_(is_static_pos)
	, mouse_on_(false)
	, lbutton_hold_(false)
	, parent_(nullptr)
{
}

Ui::~Ui()
{
	SafeDeleteVector<Ui*>(children_);
}



void Ui::Update()
{
	
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(Core::GetInstance()->get_main_hwnd(), &pt);
	Vector2 mouse_pos{ pt };
	Vector2 pos = get_final_pos();
	Vector2 scale = get_scale();
	//ȭ�� �ȿ��� ���콺 �̺�Ʈ�� �Ͼ�� ��츸
	if (Vector2{ 0, 0 } <= mouse_pos && mouse_pos <= Core::GetInstance()->get_resolution()) {
		//mouse ��ǥ�� �׻� ȭ���� �������� �� render ��ǥ�̹Ƿ� world ��ǥ�� ��ȯ����.
		mouse_pos = RenderToWorldPos(mouse_pos);
		//pos�� �� ui�� static pos�� ����ϰ� ���� ��쿡�� world ��ǥ�� ��ȯ����.
		if (is_static_pos_) pos = RenderToWorldPos(pos);

		mouse_on_ = (pos <= mouse_pos && mouse_pos <= pos + scale);

	}
	else {
		mouse_on_ = false;
	}

	ChildrenUpdate();
}

void Ui::FinalUpdate()
{
	final_pos_ = get_pos();
	//�ڽ��� ���: �θ��� 0,0�� �������� �� �����ǥ��.
	if (get_parent() != nullptr) {
		final_pos_ += get_parent()->get_pos();
	}

	ChildrenFinalUpdate();
}


//=============================================================
//
//		�ڽ� Ui Ŭ�������� Update, FinalUpdate, Render �Ŀ�
//		���������� �ϴ� �Լ���.
//
//=============================================================
void Ui::ChildrenUpdate()
{
	for (auto iter = children_.begin(); iter != children_.end(); iter++) {
		(*iter)->Update();
	}
}

void Ui::ChildrenFinalUpdate()
{
	for (auto iter = children_.begin(); iter != children_.end(); iter++) {
		(*iter)->FinalUpdate();
	}
}


void Ui::ChildrenRender(HDC hdc)
{
	for (auto iter = children_.begin(); iter != children_.end(); iter++) {
		(*iter)->Render(hdc);
	}
}