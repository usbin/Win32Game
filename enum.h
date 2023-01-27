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
	BACKSPACE,
	ENTER,
	ESC,
	KEY_GRAVE,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_0,
	KEY_MINUS,
	KEY_PLUS,
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
	DEFAULT = 0,
	BACKGROUND1 = 2,
	BACKGROUND2 = 3,
	BACKGROUND3 = 4,
	TILE = 5,			//�� �������� ���Ǵ� Ÿ��
	TILE_OBJECT,	//��, �۹�, �� �� Ÿ�� 1���� �����ϴ� ������Ʈ. ��ü NxM�� �����͸� �� �ȿ��� �����ؾ���.
	DROP_ITEM,
	SHIPPING_BOX,
	PLAYER,
	THING,
	MISSILE,
	MONSTER,
	TOPGROUND,
	DARKNESS,
	DIRECTOR,
	INTERACTOR = 29,
	INVISIBLE_WALL = 30,
	UI = 31, //�� �������� ������
	END = 32
};

enum class SCENE_TYPE
{
	TITLE,
	SCENE_FARM,
	SCENE_FARMHOUSE,
	SCENE_TOOL,
	END
};

enum class ITEM_CODE {
	HOE				= 1,	//����
	WATERING_POT	= 2,	//���Ѹ���
	PICKAXE			= 3,	//���
	AXE				= 4,	//����
	STONE			= 50,	//��
	WOOD			= 51,	//����
	WEED			= 52,	//����
	PARSNIP_SEED	= 100,	//���� ����
	PARSNIP			= 101,	//����
	END

};

enum class TILE_OBJECT_TYPE {
	STONE,
	WOOD,
	WEED,
	FIELD,
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
	UP,
	DOWN,
	LEFT,
	RIGHT,
	END
};

enum class PLAYER_STATE {
	IDLE,
	WALK,
	RUN,
	END
};
enum class PLAYER_HAND_STATE {
	NONE,
	HOLD,
	EQUIP,
	END
};



enum class EFFECT_STATE
{
	PREVIOUS,	//���� ȿ�� ���� ��
	PLAYING,	//ȿ�� ���� ��
	DONE		//ȿ�� ����
};

enum class RENDER_LAYER
{
	GROUND,
	PLAYER,
	TOP,
	END
};
