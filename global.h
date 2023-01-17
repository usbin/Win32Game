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
#include <utility>
#include <cmath>
#include <map>
#include <cassert>
#include <memory>
//Direct3D 11 ���
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
// �ؽ�Ʈ ������ :: DirectWrite, Direct2D ���
//==============================================
#pragma comment(lib, "D2d1.lib")
#pragma comment(lib, "Dwrite.lib")
#include <dwrite.h>
#include <d2d1.h>

typedef std::basic_string<TCHAR> tstring;

#pragma comment(lib, "Msimg32.lib")
#include "macro.h"
#include "struct.h"
#include "enum.h"
#include "inline.h"
#include "function.h"
#include "SelectGdi.h"



#define TILE_WIDTH 48
#define TILE_HEIGHT 48


const int CELL_COUNT_INLINE = (static_cast<int>(KEY::KEY_PLUS) - static_cast<int>(KEY::KEY_1) + 1);
const int CELL_COUNT_MAX = CELL_COUNT_INLINE * 3;

typedef int GAME_STATE;
const GAME_STATE GAME_STATE_TIME_STOPPED = 0x10;	// �ð� ����¡ ����(���� �������� ���ݵǴ� �̺�Ʈ �߻� ���� �� ��)
const GAME_STATE GAME_STATE_PLAYER_FREEZED = 0x1;	// �÷��̾� ����¡ ����