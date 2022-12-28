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
	F1,
	F2,
	F3,
	F4,
	F5,
	F11,
	F12,
	LAST, //������ üũ��
};




enum class GROUP_TYPE
{
	DEFAULT=0,
	BACKGROUND=2,
	TILE=3,
	PLAYER,
	THING,
	MISSILE,
	MONSTER,
	DIRECTOR,
	INTERACTOR = 29,
	INVISIBLE_WALL = 30,
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
	BLACK_DASH,
	END
};

enum class BRUSH_TYPE { 
	WHITE,
	BLACK,
	BRIGHT_GRAY,
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

enum class GAME_STATE
{
	PLAYING,		// �ð��� �귯���� �÷��̾ ������ �� �ִ� ����
	TIME_STOPPED,	// �ð��� ���߰� �÷��̾�� �����̴� ����(���� �������� ���ݵǴ� �̺�Ʈ �߻� ���� �� ��)
	PLAYER_FREEZED,	// �ð��� �귯���� �÷��̾ ���� ����
	FREEZED			// �ð��� ���߰� �÷��̾ ������ �� ���� ����
};

enum class EFFECT_STATE
{
	PREVIOUS,	//���� ȿ�� ���� ��
	PLAYING,	//ȿ�� ���� ��
	DONE		//ȿ�� ����
};

//====================
// �ؽ�Ʈ ��¿�
//=====================
enum class TEXT_BRUSHES {
	BLACK,
	END
};
enum class FONT
{
	Arial,
	DUNGGEONMO,
	END
};


