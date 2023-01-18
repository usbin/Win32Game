#include "KeyManager.h"
#include "SceneManager.h"
#include "Core.h"

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
	VK_TAB,	//TAB
	VK_BACK, //Backspace
	VK_RETURN, //Enter
	0xC0,	//`키(Grave)
	0x31,	//1
	0x32,	//2
	0x33,	//3
	0x34,	//4
	0x35,	//5
	0x36,	//6
	0x37,	//7
	0x38,	//8
	0x39,	//9
	0x30,	//0
	VK_OEM_MINUS,	//-
	VK_OEM_PLUS,	//+
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
	VK_F1,
	VK_F2,
	VK_F3,
	VK_F4,
	VK_F5,
	VK_F11,
	VK_F12
};
KeyManager::KeyManager() {}
KeyManager::~KeyManager() {}




bool KeyManager::Init() {
	
	//current_key_states 초기화
	for (int i=0; i < static_cast<int>(KEY::LAST); i++) {
		current_key_states_.push_back(CurrentKeyState{ KEY_STATE::NONE, FALSE });
	}
	return TRUE;
}
bool KeyManager::Update()
{
	//프로그램이 포커싱됨
	if (GetFocus() != nullptr) {
		for (int i = 0; i < static_cast<int>(KEY::LAST); i++) {
			//키 눌린 상태
			if (GetAsyncKeyState(g_windows_keys[i]) & 0x8000) {
				//이전 프레임에서 눌리지 않음 -> 최초 입력(DOWN)
				if (!current_key_states_[i].prev_pressed) {
					current_key_states_[i].state = KEY_STATE::DOWN;
				}
				//이전 프레임에서도 눌림 -> HOLD
				else {
					current_key_states_[i].state = KEY_STATE::HOLD;
				}
				current_key_states_[i].prev_pressed = TRUE;
			}
			//키 눌리지 않은 상태
			else {
				//이전 프레임에서 눌림 -> 키 떨어짐(UP)
				if (current_key_states_[i].prev_pressed) {
					current_key_states_[i].state = KEY_STATE::UP;
				}
				//이전 프레임에서 눌리지 않음 -> NONE
				else {
					current_key_states_[i].state = KEY_STATE::NONE;
				}
				current_key_states_[i].prev_pressed = FALSE;
			}
		}
		//마우스가 창 안에서 눌렸는지 저장
		POINT pt_mouse_pos;
		GetCursorPos(&pt_mouse_pos);
		ScreenToClient(Core::GetInstance()->get_main_hwnd(), &pt_mouse_pos);
		Vector2 mouse_pos = Vector2{ pt_mouse_pos };
		Vector2 resolution = Core::GetInstance()->get_resolution();
		if (mouse_pos.x > 0 && mouse_pos.y > 0
			&& mouse_pos.x < resolution.x && mouse_pos.y < resolution.y) {
			mouse_in_window_ = true;
		}
		else {
			mouse_in_window_ = false;
		}

		mouse_pos_ = RenderToWorldPos(Vector2{ pt_mouse_pos });
	}
	//프로그램이 포커싱되어 있지 않음 -> 자연스럽게 키가 떨어진 것처럼 바꿈
	else {
		for (int i = 0; i < static_cast<int>(KEY::LAST); i++) {
			//이전 프레임에서 눌렸었음 -> 떨어짐(UP) 상태로 변경
			if (current_key_states_[i].prev_pressed) {
				current_key_states_[i].state = KEY_STATE::UP;
			}
			//이전 프레임에서 눌리지 않았음 -> NONE 상태로 변경
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

