#pragma once



#define _CRTDBG_MAP_ALLOC
#define _INC_MALLOC
#include <stdlib.h>
#include <crtdbg.h>	
#include <time.h>

#define DEBUG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)


#include <Windows.h>
#include <tchar.h>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <deque>
#include <utility>
#include <cmath>
#include <map>
#include <cassert>
#include <memory>
#include <iostream>
#include <sstream>
#include <cmath>
//Direct3D 11 사용
#pragma comment(lib, "D3D11.lib")
#pragma comment(lib, "D3DX11.lib")
#pragma comment(lib, "D3dCompiler.lib")
#include <d3d11.h>
#include <D3DX11.h>
#include <D3DX11tex.h>
#include <d3dcompiler.h>
#include <D3DX11async.h>
#include <DirectXMath.h>
using namespace DirectX;
//===============================================
// 텍스트 렌더링 :: DirectWrite, Direct2D 사용
//==============================================
#pragma comment(lib, "D2d1.lib")
#pragma comment(lib, "Dwrite.lib")
#include <dwrite.h>
#include <d2d1.h>
#pragma comment(lib, "Msimg32.lib")
//=============================================
// 사운드 라이브러리 : FMOD
//=============================================
#pragma comment(lib, "fmod_vc.lib")
#include <fmod.hpp>

typedef std::basic_string<TCHAR> tstring;

typedef std::basic_ios<TCHAR, std::char_traits<TCHAR>> tios;
typedef std::basic_streambuf<TCHAR, std::char_traits<TCHAR>> tstreambuf;
typedef std::basic_istream<TCHAR, std::char_traits<TCHAR>> tistream;
typedef std::basic_ostream<TCHAR, std::char_traits<TCHAR>> tostream;
typedef std::basic_iostream<TCHAR, std::char_traits<TCHAR>> tiostream;
typedef std::basic_stringbuf<TCHAR, std::char_traits<TCHAR>,  std::allocator<TCHAR>> tstringbuf;
typedef std::basic_istringstream<TCHAR, std::char_traits<TCHAR>,  std::allocator<TCHAR>> tistringstream;
typedef std::basic_ostringstream<TCHAR, std::char_traits<TCHAR>,  std::allocator<TCHAR>> tostringstream;
typedef std::basic_stringstream<TCHAR, std::char_traits<TCHAR>,  std::allocator<TCHAR>> tstringstream;
typedef std::basic_filebuf<TCHAR, std::char_traits<TCHAR>> tfilebuf;
typedef std::basic_ifstream<TCHAR, std::char_traits<TCHAR>> tifstream;
typedef std::basic_ofstream<TCHAR, std::char_traits<TCHAR>> tofstream;
typedef std::basic_fstream<TCHAR, std::char_traits<TCHAR>> tfstream;


#include "macro.h"
#include "struct.h"
#include "enum.h"

#define TILE_WIDTH 48
#define TILE_HEIGHT 48


const int CELL_COUNT_INLINE = (static_cast<int>(KEY::KEY_PLUS) - static_cast<int>(KEY::KEY_1) + 1);
const int CELL_COUNT_MAX = CELL_COUNT_INLINE * 3;

typedef int GAME_STATE;
const GAME_STATE GAME_STATE_CONTROL_FREEZED = 0b001;// 아무 키도 누르지 못하고 지켜봐야 할 때
const GAME_STATE GAME_STATE_TIME_STOPPED = 0b010;	// 시간 프리징 여부(자유 움직임이 동반되는 이벤트 발생 중일 때 등)
//const GAME_STATE GAME_STATE_PLAYER_FREEZED = 0b100;	// 플레이어 프리징 여부

#include "inline.h"
#include "function.h"
#include "SelectGdi.h"


