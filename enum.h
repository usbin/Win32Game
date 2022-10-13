#pragma once

enum class KEY_STATE {
	UP, HOLD, DOWN, NONE
};

enum class KEY { //KeyManager.cpp�� g_windows_keys���� ���� ������ �߰��ؾ���.
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
	TAB,
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
	LAST, //������ üũ��
};




enum class GROUP_TYPE
{
	DEFAULT=0,
	BACKGROUND=1,
	TILE=2,
	PLAYER,
	THING,
	MISSILE,
	MONSTER,
	DIRECTOR,
	UI = 31, //�� �������� ������
	END = 32
};
enum class SCENE_TYPE
{
	TITLE,
	SCENE_01,
	SCENE_TOOL,
	END
};

enum class PEN_TYPE {//void Core::InitPenAndBrush()���� �ʱ�ȭ ���� �߰��ؾ���
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
	MAGENTA,
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