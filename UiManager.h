#pragma once
#include "global.h"
class Ui;
//�������� ��� Ui�� ��ȸ�ϸ� MOUSE_CLICK, MOUSE_ON, MOUSE_UP, MOUSE_DOWN�� üũ�ϰ� �ݹ��� ��������ִ� �Ŵ���
class UiManager
{
	SINGLETON(UiManager);
private:
	Ui* prev_downed_target;		//�ֱٿ� DOWN�� Ui�� �����ϰ� �ִٰ� UP ������ ��ġ�ϸ� CLICK �̺�Ʈ�� ����.
public:
	void FinalUpdate();

};

