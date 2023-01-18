#pragma once
#include "global.h"
class Core;

struct CurrentKeyState {
	KEY_STATE state;
	bool prev_pressed;
};
class KeyManager
{
	SINGLETON(KeyManager);
private:
	std::vector<CurrentKeyState> current_key_states_;
	Vector2 mouse_pos_ = Vector2::Zero();
	bool mouse_in_window_ = false;
public:
	bool Init();
	bool Update();
	inline KEY_STATE get_key_states(KEY key) { return current_key_states_[static_cast<int>(key)].state; }
	int ToWindowsKey(KEY key);
	inline Vector2 GetMousePos() { return mouse_pos_; };
	inline bool IsMouseInWindow() { return mouse_in_window_; };
	void Reset();//키입력 리셋

	friend class Core;
};

