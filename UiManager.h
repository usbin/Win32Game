#pragma once
#include "global.h"
class Ui;
//�������� ��� Ui�� ��ȸ�ϸ� MOUSE_CLICK, MOUSE_ON, MOUSE_UP, MOUSE_DOWN�� üũ�ϰ� �ݹ��� ��������ִ� �Ŵ���
class UiManager
{
	SINGLETON(UiManager);
private:
	Ui* prev_downed_target_ = nullptr;		//�ֱٿ� DOWN�� Ui�� �����ϰ� �ִٰ� UP ������ ��ġ�ϸ� CLICK �̺�Ʈ�� ����.
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

