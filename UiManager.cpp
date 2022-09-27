#include "UiManager.h"
#include "SceneManager.h"
#include "Ui.h"

UiManager::UiManager() {

}

UiManager::~UiManager() {

}

void UiManager::FinalUpdate()
{
	//[1] 타깃 ui의 루트 ui를 맨 위로 올리기
	//[2] 타깃 ui에 대하여 마우스 이벤트 발생
	//[3] 타깃 ui 제외한 모든 ui에 대하여 초기화해줄 항목 초기화(상태 변수 등)

	//1. 마우스 위치의 맨 위에 있는 ui를 찾기(=마우스가 올려져 있으면서 벡터의 가장 뒤에 있는 ui)
	// - 현재 씬의 모든 Ui에서 가져옴.

	const std::vector<GObject*>& uis = SceneManager::GetInstance()->get_current_scene()->GetGroupObjects(GROUP_TYPE::UI);
	std::vector<GObject*> ui_heap = uis; // bfs 탐색용 힙(모든 자식들 계층 순서(너비 우선)대로 탐색)
	Ui* target_ui = nullptr;
	for (int i = 0; i < ui_heap.size(); i++) {
		Ui* ui = static_cast<Ui*>(ui_heap[i]);
		
		for (int j = 0; j < ui->get_children().size(); j++) {
			ui_heap.push_back(ui->get_children()[j]);
		}
		//이번 프레임에 target_ui가 확실히 아닌 것은 전부 lbutton_hold를 false로 설정해줌. 
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

	// - target_ui는 확정적으로 MOUSE_ON인 상태
	// - prev_downed_target은 이전에 클릭한 ui가 저장돼있음.
	//2. MOUSE_ON된 target_ui에 대하여 모든 마우스 이벤트 검사(ON 제외 아무 이벤트도 발생하지 않았을 수도 있음)
	if (target_ui != nullptr) {
		target_ui->MouseOn();
		// 이번 프레임의 마우스 상태가 DOWN임 = MOUSE_DOWN
		if (KEY_DOWN(KEY::LBUTTON)) {
			target_ui->MouseDown();
			prev_downed_target = target_ui;
			SceneManager::GetInstance()->get_current_scene()->ObjectToTop(GROUP_TYPE::UI, dynamic_cast<GObject*>(target_ui_root));
		}
		// 이번 프레임의 마우스 상태가 UP임 = MOUSE_UP
		else if (KEY_UP(KEY::LBUTTON)) {
			target_ui->MouseUp();
			if (prev_downed_target == target_ui) {
				target_ui->MouseClick();
			}
			prev_downed_target = nullptr;
		}

		target_ui->set_lbutton_hold(KEY_HOLD(KEY::LBUTTON));
		
	}
	// ui가 아닌 곳에서 마우스가 떼어졌을 경우 -> prev_downed_target 초기화
	else if (KEY_UP(KEY::LBUTTON)) {
		prev_downed_target = nullptr;
	}
	
	
}
