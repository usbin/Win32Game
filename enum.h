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
	LAST, //마지막 체크용
};




enum class GROUP_TYPE
{
	DEFAULT = 0,
	BACKGROUND1 = 2,
	BACKGROUND2 = 3,
	BACKGROUND3 = 4,
	TILE = 5,			//툴 씬에서만 사용되는 타일
	TILE_OBJECT,	//밭, 작물, 돌 등 타일 1개를 차지하는 오브젝트. 전체 NxM의 포인터를 씬 안에서 유지해야함.
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
	UI = 31, //맨 마지막에 렌더링
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
	HOE				= 1,	//괭이
	WATERING_POT	= 2,	//물뿌리개
	PICKAXE			= 3,	//곡괭이
	AXE				= 4,	//도끼
	STONE			= 50,	//돌
	WOOD			= 51,	//나무
	WEED			= 52,	//잡초
	PARSNIP_SEED	= 100,	//순무 씨앗
	PARSNIP			= 101,	//순무
	END

};

enum class TILE_OBJECT_TYPE {
	STONE,
	WOOD,
	WEED,
	FIELD,
	END
};
enum class PEN_TYPE {//void Core::InitPenAndBrush()에도 초기화 구문 추가해야함
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
	PREVIOUS,	//아직 효과 시작 전
	PLAYING,	//효과 실행 중
	DONE		//효과 끝남
};

enum class RENDER_LAYER
{
	GROUND,
	PLAYER,
	TOP,
	END
};
