#pragma once
#include "global.h"
class Ui;
//매프레임 모든 Ui를 순회하며 MOUSE_CLICK, MOUSE_ON, MOUSE_UP, MOUSE_DOWN를 체크하고 콜백을 실행시켜주는 매니저
class UiManager
{
	SINGLETON(UiManager);
private:
	Ui* prev_downed_target_ = nullptr;		//최근에 DOWN된 Ui를 저장하고 있다가 UP 시점에 일치하면 CLICK 이벤트로 간주.
	Ui* target_ui_ = nullptr;

	Ui* selected_target_ = nullptr;
	void Dfs(const std::vector<Ui*>& uis, std::vector<Ui*>& ui_heap);
public:
	void FinalUpdate();
	inline Ui* get_selected_target() {
		return selected_target_;
	};
	inline bool focus_nothing() { return !target_ui_ && !prev_downed_target_; };
	void ResetSelection();
};

