#include "UiManager.h"
#include "SceneManager.h"
#include "Ui.h"

UiManager::UiManager() {

}

UiManager::~UiManager() {

}

void UiManager::FinalUpdate()
{
	//[1] Ÿ�� ui�� ��Ʈ ui�� �� ���� �ø���
	//[2] Ÿ�� ui�� ���Ͽ� ���콺 �̺�Ʈ �߻�
	//[3] Ÿ�� ui ������ ��� ui�� ���Ͽ� �ʱ�ȭ���� �׸� �ʱ�ȭ(���� ���� ��)

	//1. ���콺 ��ġ�� �� ���� �ִ� ui�� ã��(=���콺�� �÷��� �����鼭 ������ ���� �ڿ� �ִ� ui)
	// - ���� ���� ��� Ui���� ������.

	const std::vector<GObject*>& uis = SceneManager::GetInstance()->get_current_scene()->GetGroupObjects(GROUP_TYPE::UI);
	std::vector<GObject*> ui_heap = uis; // bfs Ž���� ��(��� �ڽĵ� ���� ����(�ʺ� �켱)��� Ž��)
	Ui* target_ui = nullptr;
	for (int i = 0; i < ui_heap.size(); i++) {
		Ui* ui = static_cast<Ui*>(ui_heap[i]);
		
		for (int j = 0; j < ui->get_children().size(); j++) {
			ui_heap.push_back(ui->get_children()[j]);
		}
		//�̹� �����ӿ� target_ui�� Ȯ���� �ƴ� ���� ���� lbutton_hold�� false�� ��������. 
		if (ui->get_mouse_on()) {
			if (target_ui != nullptr) {
				target_ui -> set_lbutton_hold(false);
			}
			target_ui = ui;
		}
		else {
			ui->set_lbutton_hold(false);
		}
	}


	Ui* target_ui_root = target_ui;
	if (target_ui_root != nullptr) {
		while (target_ui_root->get_parent() != nullptr) {
			target_ui_root = target_ui_root->get_parent();
		}
	}

	// - target_ui�� Ȯ�������� MOUSE_ON�� ����
	// - prev_downed_target�� ������ Ŭ���� ui�� ���������.
	//2. MOUSE_ON�� target_ui�� ���Ͽ� ��� ���콺 �̺�Ʈ �˻�(ON ���� �ƹ� �̺�Ʈ�� �߻����� �ʾ��� ���� ����)
	if (target_ui != nullptr) {
		target_ui->MouseOn();
		// �̹� �������� ���콺 ���°� DOWN�� = MOUSE_DOWN
		if (KEY_DOWN(KEY::LBUTTON)) {
			target_ui->MouseDown();
			prev_downed_target = target_ui;
			SceneManager::GetInstance()->get_current_scene()->ObjectToTop(GROUP_TYPE::UI, dynamic_cast<GObject*>(target_ui_root));
		}
		// �̹� �������� ���콺 ���°� UP�� = MOUSE_UP
		else if (KEY_UP(KEY::LBUTTON)) {
			target_ui->MouseUp();
			if (prev_downed_target == target_ui) {
				target_ui->MouseClick();
			}
			prev_downed_target = nullptr;
		}

		target_ui->set_lbutton_hold(KEY_HOLD(KEY::LBUTTON));
		
	}
	// ui�� �ƴ� ������ ���콺�� �������� ��� -> prev_downed_target �ʱ�ȭ
	else if (KEY_UP(KEY::LBUTTON)) {
		prev_downed_target = nullptr;
	}
	
	
}
