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
	//선택하고 있던 Ui가 삭제되면 참조 해제
	if (selected_target_ && (selected_target_->IsDead() || !selected_target_->get_enabled())) {
		selected_target_->Unselect();
		selected_target_ = nullptr;
	}
	//선택하고 있던 Ui가 선택 불가 상태로 바뀌면 선택해제
	if (selected_target_ && (!selected_target_->get_is_selectable() || !selected_target_->get_enabled())) {
		selected_target_->Unselect();
	}

	//[1] 타깃 ui의 루트 ui를 맨 위로 올리기
	//[2] 타깃 ui에 대하여 마우스 이벤트 발생
	//[3] 타깃 ui 제외한 모든 ui에 대하여 초기화해줄 항목 초기화(상태 변수 등)

	//1. 마우스 위치의 맨 위에 있는 ui를 찾기(=마우스가 올려져 있으면서 벡터의 가장 뒤에 있는 ui)
	// - 현재 씬의 모든 Ui에서 가져옴.

	const std::vector<GObject*>& uis = SceneManager::GetInstance()->get_current_scene()->GetGroupObjects(GROUP_TYPE::UI);
	std::vector<Ui*> ui_heap;// dfs 탐색용 힙(모든 자식들 계층 순서(깊이 우선)대로 탐색)
	//uis의 첫 항목부터 모든 자식을 탐색하며 체크하고 다음 항목으로 넘어감.
	for (int i = 0; i < uis.size(); i++) {
		Ui* ui = static_cast<Ui*>(uis[i]);
		ui_heap.push_back(ui);
		Dfs(ui->get_children(), ui_heap);
	}

	target_ui_ = nullptr;
	for (int i = 0; i < ui_heap.size(); i++) {
		Ui* ui = static_cast<Ui*>(ui_heap[i]);
		//이번 프레임에 target_ui가 확실히 아닌 것은 전부 lbutton_hold를 false로 설정해줌. 
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

	// - target_ui는 확정적으로 MOUSE_ON인 상태
	// - prev_downed_target은 이전에 클릭한 ui가 저장돼있음.
	//2. MOUSE_ON된 target_ui에 대하여 모든 마우스 이벤트 검사(ON 제외 아무 이벤트도 발생하지 않았을 수도 있음)
	if (target_ui_ != nullptr) {
		target_ui_->MouseOn();
		target_ui_->set_lbutton_hold(KEY_HOLD(KEY::LBUTTON));
		// 이번 프레임의 마우스 상태가 DOWN임 = MOUSE_DOWN
		if (KEY_DOWN(KEY::LBUTTON)) {
			target_ui_->LbuttonDown();
			prev_downed_target_ = target_ui_;
			//Panel일 경우 Top으로 올림.
			if (dynamic_cast<PanelUi*>(target_ui_root)) {
				SceneManager::GetInstance()->get_current_scene()->ObjectToTop(GROUP_TYPE::UI, dynamic_cast<GObject*>(target_ui_root));
			}
			
		}
		// 이번 프레임의 마우스 상태가 UP임 = MOUSE_UP
		else if (KEY_UP(KEY::LBUTTON)) {
			target_ui_->LbuttonUp();
			if (prev_downed_target_ == target_ui_) {
				target_ui_->LbuttonClick();
				// 선택된 ui가 변경됨 : Select
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
	// ui가 아닌 곳에서 마우스가 떼어졌을 경우 -> prev_downed_target 초기화
	else if (KEY_UP(KEY::LBUTTON)) {
		prev_downed_target_ = nullptr;
	}

	// selected_target_이 DEAD일 경우 해제된 다음 참조하지 않도록 참조 해제
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
