#pragma once
#include "KeyManager.h"

inline bool KEY_CHECK(KEY key, KEY_STATE state) { return KeyManager::GetInstance()->get_key_states(key) == state; };
inline bool KEY_DOWN(KEY key) { return KEY_CHECK(key, KEY_STATE::DOWN); };
inline bool KEY_HOLD(KEY key) { return KEY_CHECK(key, KEY_STATE::HOLD); };
inline bool KEY_UP(KEY key) { return KEY_CHECK(key, KEY_STATE::UP); };
inline Vector2 GET_MOUSE_POS() {
	return KeyManager::GetInstance()->GetMousePos();
}
inline bool MOUSE_IN_WINDOW() {
	return KeyManager::GetInstance()->IsMouseInWindow();
}