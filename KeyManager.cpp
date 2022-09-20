#include "pch.h"
#include "KeyManager.h"
#include "SceneManager.h"

int g_windows_keys[static_cast<int>(KEY::LAST)] = {
	VK_LBUTTON,//LBUTTON,
	VK_RBUTTON,//RBUTTON,
	VK_UP,//UP,
	VK_DOWN,//DOWN,
	VK_LEFT,//LEFT,
	VK_RIGHT,//RIGHT,
	VK_SHIFT,//SHIFT,
	VK_CONTROL,//CTRL,
	VK_MENU,//ALT,
	VK_SPACE, //SPACE
	'Q',//Q,
	'W',//W,
	'E',//E,
	'R',//R,
	'T',//T,
	'Y',//Y,
	'U',//U,
	'I',//I,
	'O',//O,
	'P',//P,
	'A',//A,
	'S',//S,
	'D',//D,
	'F',//F,
	'G',//G,
	'H',//H,
	'J',//J,
	'K',//K,
	'L',//L,
	'Z',//Z,
	'X',//X,
	'C',//C,
	'V',//V,
	'B',//B,
	'N',//N,
	'M',//M,
};
KeyManager::KeyManager() {}
KeyManager::~KeyManager() {}




bool KeyManager::Init() {
	
	//current_key_states �ʱ�ȭ
	for (int i=0; i < static_cast<int>(KEY::LAST); i++) {
		current_key_states_.push_back(CurrentKeyState{ KEY_STATE::NONE, FALSE });
	}
	return TRUE;
}
bool KeyManager::Update()
{
	//���α׷��� ��Ŀ�̵�
	if (GetFocus() != nullptr) {
		for (int i = 0; i < static_cast<int>(KEY::LAST); i++) {
			//Ű ���� ����
			if (GetAsyncKeyState(g_windows_keys[i]) & 0x8000) {
				//���� �����ӿ��� ������ ���� -> ���� �Է�(DOWN)
				if (!current_key_states_[i].prev_pressed) {
					current_key_states_[i].state = KEY_STATE::DOWN;
				}
				//���� �����ӿ����� ���� -> HOLD
				else {
					current_key_states_[i].state = KEY_STATE::HOLD;
				}
				current_key_states_[i].prev_pressed = TRUE;
			}
			//Ű ������ ���� ����
			else {
				//���� �����ӿ��� ���� -> Ű ������(UP)
				if (current_key_states_[i].prev_pressed) {
					current_key_states_[i].state = KEY_STATE::UP;
				}
				//���� �����ӿ��� ������ ���� -> NONE
				else {
					current_key_states_[i].state = KEY_STATE::NONE;
				}
				current_key_states_[i].prev_pressed = FALSE;
			}
		}
	}
	//���α׷��� ��Ŀ�̵Ǿ� ���� ���� -> �ڿ������� Ű�� ������ ��ó�� �ٲ�
	else {
		for (int i = 0; i < static_cast<int>(KEY::LAST); i++) {
			//���� �����ӿ��� ���Ⱦ��� -> ������(UP) ���·� ����
			if (current_key_states_[i].prev_pressed) {
				current_key_states_[i].state = KEY_STATE::UP;
			}
			//���� �����ӿ��� ������ �ʾ��� -> NONE ���·� ����
			else {
				current_key_states_[i].state = KEY_STATE::NONE;
			}
			current_key_states_[i].prev_pressed = FALSE;
			
		}
	}

	
	
	return TRUE;
}
void KeyManager::Reset()
{
	for (int i = 0; i < static_cast<int>(KEY::LAST); i++) {
		current_key_states_[i].state = KEY_STATE::NONE;
		current_key_states_[i].prev_pressed = FALSE;

	}
}


inline int KeyManager::ToWindowsKey(KEY key) { return g_windows_keys[static_cast<int>(key)]; }

