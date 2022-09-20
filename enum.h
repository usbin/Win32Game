#pragma once

enum class KEY_STATE {
	UP, HOLD, DOWN, NONE
};

enum class KEY { //KeyManager.cpp의 g_windows_keys에도 같은 순서로 추가해야함.
	LBUTTON,
	RBUTTON,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	SHIFT,
	CTRL,
	ALT,
	SPACE,
	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,
	A,
	S,
	D,
	F,
	G,
	H,
	J,
	K,
	L,
	Z,
	X,
	C,
	V,
	B,
	N,
	M,
	LAST, //마지막 체크용
};




enum class GROUP_TYPE
{
	DEFAULT,
	PLAYER,
	THING,
	MISSILE,
	MONSTER,
	END = 32
};
enum class SCENE_TYPE
{
	TITLE,
	SCENE_01,
	END
};

enum class PEN_TYPE {
	BLACK,
	WHITE,
	RED,
	GREEN,
	BLUE,
	END
};

enum class BRUSH_TYPE {
	WHITE,
	BLACK,
	RED,
	GREEN,
	BLUE,
	HOLLOW,
	END
};

enum class EVENT_TYPE {
	CREATE_OBJECT,
	DELETE_OBJECT,
	CHANGE_SCENE,
	END
};

enum class DIRECTION {
	LEFT,
	RIGHT,
	UP,
	DOWN
};