#pragma once



#define _CRTDBG_MAP_ALLOC
#define _INC_MALLOC
#include <stdlib.h>
#include <crtdbg.h>	


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
//Direct3D 11 »ç¿ë
#pragma comment(lib, "D3D11.lib")
#pragma comment(lib, "D3DX11.lib")
#pragma comment(lib, "D3dCompiler.lib")
#include <d3d11.h>
#include <D3DX11.h>
#include <D3DX10tex.h>
#include <d3dcompiler.h>
#include <D3DX11async.h>
#include <DirectXMath.h>
using namespace DirectX;

#pragma comment(lib, "Msimg32.lib")
#include "macro.h"
#include "struct.h"
#include "enum.h"
#include "inline.h"
#include "function.h"
#include "SelectGdi.h"

typedef std::basic_string<TCHAR> tstring;

