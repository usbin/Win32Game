#pragma once

struct CurrentKeyState {
	KEY_STATE state;
	bool prev_pressed;
};
class KeyManager
{
	SINGLETON(KeyManager);
private:
	std::vector<CurrentKeyState> current_key_states_;
public:
	bool Init();
	bool Update();
	inline KEY_STATE get_key_states(KEY key) { return current_key_states_[static_cast<int>(key)].state; }
	int ToWindowsKey(KEY key);
	void Reset();//키입력 리셋
};

