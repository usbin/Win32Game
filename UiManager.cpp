#include "UiManager.h"
#include "SceneManager.h"
#include "Ui.h"
#include "PanelUi.h"

UiManager::UiManager() 
	:prev_downed_target_(nullptr){

}

UiManager::~UiManager() {

}
void UiManager::Dfs(const std::vector<Ui*>& uis, std::vector<Ui*>& ui_heap) {
	if (uis.size() == 0) {
		return;
	}
	else {
		for (int i = 0; i < uis.size(); i++) {
			ui_heap.push_back(uis[i]);
			Dfs(static_cast<Ui*>(uis[i])->get_children(), ui_heap);
		}
	}
}
void UiManager::FinalUpdate()
{
	//�����ϰ� �ִ� Ui�� �����Ǹ� ���� ����
	if (selected_target_ && (selected_target_->IsDead() || !selected_target_->get_enabled())) {
		selected_target_->Unselect();
		selected_target_ = nullptr;
	}
	//�����ϰ� �ִ� Ui�� ���� �Ұ� ���·� �ٲ�� ��������
	if (selected_target_ && (!selected_target_->get_is_selectable() || !selected_target_->get_enabled())) {
		selected_target_->Unselect();
	}

	//[1] Ÿ�� ui�� ��Ʈ ui�� �� ���� �ø���
	//[2] Ÿ�� ui�� ���Ͽ� ���콺 �̺�Ʈ �߻�
	//[3] Ÿ�� ui ������ ��� ui�� ���Ͽ� �ʱ�ȭ���� �׸� �ʱ�ȭ(���� ���� ��)

	//1. ���콺 ��ġ�� �� ���� �ִ� ui�� ã��(=���콺�� �÷��� �����鼭 ������ ���� �ڿ� �ִ� ui)
	// - ���� ���� ��� Ui���� ������.

	const std::vector<GObject*>& uis = SceneManager::GetInstance()->get_current_scene()->GetGroupObjects(GROUP_TYPE::UI);
	std::vector<Ui*> ui_heap;// dfs Ž���� ��(��� �ڽĵ� ���� ����(���� �켱)��� Ž��)
	//uis�� ù �׸���� ��� �ڽ��� Ž���ϸ� üũ�ϰ� ���� �׸����� �Ѿ.
	for (int i = 0; i < uis.size(); i++) {
		Ui* ui = static_cast<Ui*>(uis[i]);
		ui_heap.push_back(ui);
		Dfs(ui->get_children(), ui_heap);
	}

	target_ui_ = nullptr;
	for (int i = 0; i < ui_heap.size(); i++) {
		Ui* ui = static_cast<Ui*>(ui_heap[i]);
		//�̹� �����ӿ� target_ui�� Ȯ���� �ƴ� ���� ���� lbutton_hold�� false�� ��������. 
		if (ui->get_mouse_on()) {
			if (target_ui_ != nullptr && target_ui_ != ui) {
				target_ui_ -> set_lbutton_hold(false);
			}
			target_ui_ = ui;
		}
		else {
			ui->set_lbutton_hold(false);
		}
	}

	Ui* target_ui_root = target_ui_;
	if (target_ui_root != nullptr) {
		while (target_ui_root->get_parent() != nullptr) {
			target_ui_root = target_ui_root->get_parent();
		}
	}

	// - target_ui�� Ȯ�������� MOUSE_ON�� ����
	// - prev_downed_target�� ������ Ŭ���� ui�� ���������.
	//2. MOUSE_ON�� target_ui�� ���Ͽ� ��� ���콺 �̺�Ʈ �˻�(ON ���� �ƹ� �̺�Ʈ�� �߻����� �ʾ��� ���� ����)
	if (target_ui_ != nullptr) {
		target_ui_->MouseOn();
		target_ui_->set_lbutton_hold(KEY_HOLD(KEY::LBUTTON));
		// �̹� �������� ���콺 ���°� DOWN�� = MOUSE_DOWN
		if (KEY_DOWN(KEY::LBUTTON)) {
			target_ui_->LbuttonDown();
			prev_downed_target_ = target_ui_;
			//Panel�� ��� Top���� �ø�.
			if (dynamic_cast<PanelUi*>(target_ui_root)) {
				SceneManager::GetInstance()->get_current_scene()->ObjectToTop(GROUP_TYPE::UI, dynamic_cast<GObject*>(target_ui_root));
			}
			
		}
		// �̹� �������� ���콺 ���°� UP�� = MOUSE_UP
		else if (KEY_UP(KEY::LBUTTON)) {
			target_ui_->LbuttonUp();
			if (prev_downed_target_ == target_ui_) {
				target_ui_->LbuttonClick();
				// ���õ� ui�� ����� : Select
				if (target_ui_->get_is_selectable()) {
					if (target_ui_) {
						if (!target_ui_->get_selected()) {
							target_ui_->set_selected(true);
							target_ui_->Select();
						}
					}
					if (selected_target_ && selected_target_ != target_ui_) {
						if (selected_target_->get_selected()) {
							selected_target_->set_selected(false);
							selected_target_->Unselect();
						}
					}
					selected_target_ = target_ui_;
				}
			}
			prev_downed_target_ = nullptr;
		}

		
	}
	// ui�� �ƴ� ������ ���콺�� �������� ��� -> prev_downed_target �ʱ�ȭ
	else if (KEY_UP(KEY::LBUTTON)) {
		prev_downed_target_ = nullptr;
	}

	// selected_target_�� DEAD�� ��� ������ ���� �������� �ʵ��� ���� ����
	if (selected_target_ && selected_target_->IsDead()) {
		selected_target_ = nullptr;
	}

	
}


void UiManager::ResetSelection()
{
	if (selected_target_) {
		selected_target_->set_selected(false);
		selected_target_->Unselect();
		selected_target_ = nullptr;
	}
}

void UiManager::SelectTarget(Ui* target)
{
	ResetSelection();
	selected_target_ = target;
	if (selected_target_) {
		selected_target_->set_selected(true);
		selected_target_->Select();

	}
}
