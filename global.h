#pragma once



#define _CRTDBG_MAP_ALLOC
#define _INC_MALLOC
#include <stdlib.h>
#include <crtdbg.h>	
#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define malloc(s) _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define new new
#define malloc malloc
#endif

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
#pragma comment(lib, "Msimg32.lib")

#include "macro.h"
#include "struct.h"
#include "enum.h"
#include "inline.h"
#include "function.h"
#include "SelectGdi.h"

typedef std::basic_string<TCHAR> tstring;

