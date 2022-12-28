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
	UI = 31, //맨 마지막에 렌더링
	END = 32
};
enum class SCENE_TYPE
{
	TITLE,
	SCENE_01,
	SCENE_TOOL,
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
	LEFT,
	RIGHT,
	UP,
	DOWN
};

enum class GAME_STATE
{
	PLAYING,		// 시간이 흘러가고 플레이어가 움직일 수 있는 상태
	TIME_STOPPED,	// 시간만 멈추고 플레이어는 움직이는 상태(자유 움직임이 동반되는 이벤트 발생 중일 때 등)
	PLAYER_FREEZED,	// 시간은 흘러가고 플레이어만 멈춘 상태
	FREEZED			// 시간도 멈추고 플레이어도 움직일 수 없는 상태
};

enum class EFFECT_STATE
{
	PREVIOUS,	//아직 효과 시작 전
	PLAYING,	//효과 실행 중
	DONE		//효과 끝남
};

//====================
// 텍스트 출력용
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


