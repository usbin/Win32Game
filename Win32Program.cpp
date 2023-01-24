// Win32Program.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include "framework.h"
#include "Win32Program.h"
#include "Core.h"
#include "SceneManager.h"
#include "Scene_Tool.h"
#include "commdlg.h"
#include "PathManager.h"
#include "ResManager.h"
#include "RealObjectSprite.h"
#include "Texture.h"
#include "Background.h"
#include "FileManager.h"
#include "DXClass.h"
#include "Director_Scene_Tool.h"
#include "TileEditUi.h"
#include "Topground.h"

#define MAX_LOADSTRING 100
#define INITIAL_WINDOW_WIDTH 1024
#define INITIAL_WINDOW_HEIGHT 768


// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
HWND g_hWnd;                                    // 윈도우 전역변수
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    ChangeTilecellSize(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    ChangeTileuisTexture(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32PROGRAM, szWindowClass, 
        MAX_LOADSTRING);
    MyRegisterClass(hInstance); 
    
    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }
    
    
    if (FAILED(Core::GetInstance()->Init(g_hWnd, hInst, INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT))) {
        MessageBox(nullptr, _T("Core 초기화에 실패했습니다."), _T("ERROR"), MB_OK);
        return FALSE;
    }
    
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROGRAM));

    MSG msg;

    // 기본 메시지 루프입니다:
    
    do
    {   
        if (PeekMessage(&msg, nullptr, 0, 0, TRUE)) {
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);

            }
        }
        else {
            Core::GetInstance()->Progress();
        }
        
    } while (msg.message != WM_QUIT);


    Core::GetInstance()->OnDestroy();
    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc; // 사용자 정의 메시지 처리 함수
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROGRAM));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDR_MENU);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!g_hWnd)
   {
      return FALSE;
   }

   ShowWindow(g_hWnd, nCmdShow);
   UpdateWindow(g_hWnd);

   

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
struct MousePoint {
    WORD x;
    WORD y;
};
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            HMENU hMenu = GetMenu(hWnd);
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_CHANGE_TILECELL_SIZE:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_CHANGE_TILECELL_SIZE), hWnd, ChangeTilecellSize);
                break;
            case IDM_LOAD_TILEUI_TEXTURE:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_CHANGE_TILEUIS_TEXTURE), hWnd, ChangeTileuisTexture);
                break;
            //===============================
            //  타일맵 관리
            //================================
            case IDM_SAVE_TILEMAP_TO_TILEMAP: {
                Scene_Tool* current_scene = dynamic_cast<Scene_Tool*>(SceneManager::GetInstance()->get_current_scene());
                //툴씬에서만 동작
                if (current_scene) {
                    TCHAR file_path[256] = _T("");

                    OPENFILENAME ofn = {};
                    memset(&ofn, 0, sizeof(OPENFILENAME));
                    ofn.lStructSize = sizeof(OPENFILENAME);
                    ofn.hwndOwner = hWnd;
                    ofn.lpstrFilter = _T("Tilemap File\0*.tilemap\0");
                    ofn.lpstrFile = file_path;
                    ofn.nMaxFile = 256;


                    if (GetSaveFileName(&ofn)) {
                        if (_tcscmp(&file_path[_tcsclen(file_path) - _tcslen(_T(".tilemap"))], _T(".tilemap")))
                            _tcscat_s(file_path, _T(".tilemap"));
                        FileManager::GetInstance()->SaveTilemapFile(file_path);

                    }
                }
            }break;
            case IDM_LOAD_TILEMAP_FROM_TILEMAP: {
                //BACKGROUND, TILE, INVISIBLEWALL을 .map 파일로 저장
                Scene_Tool* current_scene = dynamic_cast<Scene_Tool*>(SceneManager::GetInstance()->get_current_scene());
                //툴씬에서만 동작
                if (current_scene) {
                    TCHAR file_path[256] = _T("");
                    TCHAR initial_path[256];
                    _tcscpy_s(initial_path, (PathManager::GetInstance()->GetContentPath()).c_str());

                    OPENFILENAME ofn = {};
                    memset(&ofn, 0, sizeof(OPENFILENAME));
                    ofn.lStructSize = sizeof(OPENFILENAME);
                    ofn.hwndOwner = hWnd;
                    ofn.lpstrFilter = _T("Tilemap File\0*.tilemap\0");
                    ofn.lpstrFile = file_path;
                    ofn.nMaxFile = 256;
                    ofn.lpstrInitialDir = initial_path;

                    if (GetOpenFileName(&ofn)) {
                        SceneManager::GetInstance()->get_current_scene()->DeleteGroupObjects(GROUP_TYPE::TILE);
                        FileManager::GetInstance()->LoadTilemapFile(file_path);
                    }
                }
            } break;
            case IDM_DELETE_TILEMAP: {
                Scene_Tool* current_scene = dynamic_cast<Scene_Tool*>(SceneManager::GetInstance()->get_current_scene());
                if (current_scene) {
                    SceneManager::GetInstance()->get_current_scene()->DeleteGroupObjects(GROUP_TYPE::TILE);

                    current_scene->CreateEmptyTilemap(current_scene->get_column_count(), current_scene->get_row_count());
                }
            }break;
            //===============================
            //  투명벽 관리
            //================================
            case IDM_SAVE_WALL: {
                Scene_Tool* current_scene = dynamic_cast<Scene_Tool*>(SceneManager::GetInstance()->get_current_scene());
                //툴씬에서만 동작
                if (current_scene) {
                    TCHAR file_path[256] = _T("");

                    OPENFILENAME ofn = {};
                    memset(&ofn, 0, sizeof(OPENFILENAME));
                    ofn.lStructSize = sizeof(OPENFILENAME);
                    ofn.hwndOwner = hWnd;
                    ofn.lpstrFilter = _T("Wall File\0*.wall\0");
                    ofn.lpstrFile = file_path;
                    ofn.nMaxFile = 256;


                    if (GetSaveFileName(&ofn)) {
                        if (_tcscmp(&file_path[_tcsclen(file_path) - _tcslen(_T(".wall"))], _T(".wall")))
                            _tcscat_s(file_path, _T(".wall"));
                        FileManager::GetInstance()->SaveWallFile(file_path);
                    }
                }
            } break;
            case IDM_LOAD_WALL: {
                //BACKGROUND, TILE, INVISIBLEWALL을 .map 파일로 저장
                Scene_Tool* current_scene = dynamic_cast<Scene_Tool*>(SceneManager::GetInstance()->get_current_scene());
                //툴씬에서만 동작
                if (current_scene) {
                    TCHAR file_path[256] = _T("");
                    TCHAR initial_path[256];
                    _tcscpy_s(initial_path, (PathManager::GetInstance()->GetContentPath()).c_str());

                    OPENFILENAME ofn = {};
                    memset(&ofn, 0, sizeof(OPENFILENAME));
                    ofn.lStructSize = sizeof(OPENFILENAME);
                    ofn.hwndOwner = hWnd;
                    ofn.lpstrFilter = _T("Wall\0*.wall\0");
                    ofn.lpstrFile = file_path;
                    ofn.nMaxFile = 256;
                    ofn.lpstrInitialDir = initial_path;

                    if (GetOpenFileName(&ofn)) {

                        //2. 복사한 맵을 불러와서, 이 맵으로 타일 리스트를 로드함.
                        //기존의 배경, 타일, 콜라이더는 전부 지워야함.
                        SceneManager::GetInstance()->get_current_scene()->DeleteGroupObjects(GROUP_TYPE::INVISIBLE_WALL);
                        FileManager::GetInstance()->LoadWallFile(file_path);
                    }
                }
            } break;
            case IDM_DELETE_WALL: {
                const std::vector<GObject*> objs = SceneManager::GetInstance()->get_current_scene()->GetGroupObjects(GROUP_TYPE::INVISIBLE_WALL);
                if (!objs.empty()) {
                    SceneManager::GetInstance()->get_current_scene()->DeleteGroupObjects(GROUP_TYPE::INVISIBLE_WALL);
                }
            }break;
            //===============================
            //  배경이미지 관리
            //================================
            case IDM_LOAD_BACKGROUND_LAYER1: {
                Scene_Tool* current_scene = dynamic_cast<Scene_Tool*>(SceneManager::GetInstance()->get_current_scene());
                if (current_scene) {
                    TCHAR file_path[256] = _T("");
                    TCHAR initial_path[256];
                    _tcscpy_s(initial_path, (PathManager::GetInstance()->GetContentPath()).c_str());

                    OPENFILENAME ofn = {};
                    memset(&ofn, 0, sizeof(OPENFILENAME));
                    ofn.lStructSize = sizeof(OPENFILENAME);
                    ofn.hwndOwner = hWnd;
                    ofn.lpstrFilter = _T("PNG\0*.png\0");
                    ofn.lpstrFile = file_path;
                    ofn.nMaxFile = 256;
                    ofn.lpstrInitialDir = initial_path;

                    if (GetOpenFileName(&ofn)) {
                        //1. 텍스쳐를 content\texture 폴더로 복사하기
                        TCHAR file_name[256] = _T("");
                        for (int i = static_cast<int>(_tcsclen(file_path))-1; i >= 0; i--) {
                            if (file_path[i] == _T('\\')) {
                                _tcscpy_s(file_name, &file_path[i + 1]);
                                break;
                            }
                        }
                        TCHAR relative_path[256] = _T("");
                        _tcscat_s(relative_path, _T("texture\\"));
                        _tcscat_s(relative_path, file_name);

                        TCHAR dest_path[256] = _T("");
                        _tcscat_s(dest_path, (PathManager::GetInstance()->GetContentPath()).c_str());
                        _tcscat_s(dest_path, relative_path);
                        CopyFile(file_path, dest_path, true);
                        //2. 복사한 텍스쳐를 불러와서, 이 텍스쳐를 1x1 스프라이트로 가지는 BACKGROUND 오브젝트 생성.
                        //이미 BACKGROUND 오브젝트가 있다면 스프라이트만 교체
                        Background* bg_object;
                        const std::vector<GObject*> objs = SceneManager::GetInstance()->get_current_scene()->GetGroupObjects(GROUP_TYPE::BACKGROUND1);
                        if (objs.empty()) {
                            bg_object = DEBUG_NEW Background();
                            CreateGObject(bg_object, GROUP_TYPE::BACKGROUND1);
                        }
                        else bg_object = dynamic_cast<Background*>(objs[0]);

                        Texture* texture = ResManager::GetInstance()->LoadTexture(file_name, relative_path);
                        RealObjectSprite* bg_sprite = DEBUG_NEW RealObjectSprite();
                        bg_sprite->QuickSet(texture, bg_object, 0, 0, 1, 1);
                        if (bg_object->get_render_component()) bg_object->get_render_component()->ChangeSprite(bg_sprite);
                        bg_object->set_group_type(GROUP_TYPE::BACKGROUND1);
                        bg_object->set_pos(Vector2{ texture->get_width(), texture->get_height() }/2.f);
                        bg_object->set_scale(Vector2{ texture->get_width(), texture->get_height() });
                        EnableMenuItem(hMenu, IDM_REMOVE_BACKGROUND_LAYER1, MF_ENABLED);
                    }
                }
                
            }  break;
            case IDM_REMOVE_BACKGROUND_LAYER1: {
                GObject* bg_object;
                const std::vector<GObject*> objs = SceneManager::GetInstance()->get_current_scene()->GetGroupObjects(GROUP_TYPE::BACKGROUND1);
                if (!objs.empty()) {
                    SceneManager::GetInstance()->get_current_scene()->DeleteGroupObjects(GROUP_TYPE::BACKGROUND1);
                }
                EnableMenuItem(hMenu, IDM_REMOVE_BACKGROUND_LAYER1, MF_DISABLED);
            } break;
            case IDM_LOAD_BACKGROUND_LAYER2:{
                Scene_Tool* current_scene = dynamic_cast<Scene_Tool*>(SceneManager::GetInstance()->get_current_scene());
                if (current_scene) {
                    TCHAR file_path[256] = _T("");
                    TCHAR initial_path[256];
                    _tcscpy_s(initial_path, (PathManager::GetInstance()->GetContentPath()).c_str());

                    OPENFILENAME ofn = {};
                    memset(&ofn, 0, sizeof(OPENFILENAME));
                    ofn.lStructSize = sizeof(OPENFILENAME);
                    ofn.hwndOwner = hWnd;
                    ofn.lpstrFilter = _T("PNG\0*.png\0");
                    ofn.lpstrFile = file_path;
                    ofn.nMaxFile = 256;
                    ofn.lpstrInitialDir = initial_path;

                    if (GetOpenFileName(&ofn)) {
                        //1. 텍스쳐를 content\texture 폴더로 복사하기
                        TCHAR file_name[256] = _T("");
                        for (int i = static_cast<int>(_tcsclen(file_path)) - 1; i >= 0; i--) {
                            if (file_path[i] == _T('\\')) {
                                _tcscpy_s(file_name, &file_path[i + 1]);
                                break;
                            }
                        }
                        TCHAR relative_path[256] = _T("");
                        _tcscat_s(relative_path, _T("texture\\"));
                        _tcscat_s(relative_path, file_name);

                        TCHAR dest_path[256] = _T("");
                        _tcscat_s(dest_path, (PathManager::GetInstance()->GetContentPath()).c_str());
                        _tcscat_s(dest_path, relative_path);
                        CopyFile(file_path, dest_path, true);
                        //2. 복사한 텍스쳐를 불러와서, 이 텍스쳐를 1x1 스프라이트로 가지는 BACKGROUND 오브젝트 생성.
                        //이미 BACKGROUND 오브젝트가 있다면 스프라이트만 교체
                        Background* bg_object;
                        const std::vector<GObject*> objs = SceneManager::GetInstance()->get_current_scene()->GetGroupObjects(GROUP_TYPE::BACKGROUND2);
                        if (objs.empty()) {
                            bg_object = DEBUG_NEW Background();
                            CreateGObject(bg_object, GROUP_TYPE::BACKGROUND2);
                        }
                        else bg_object = dynamic_cast<Background*>(objs[0]);
                        Texture* texture = ResManager::GetInstance()->LoadTexture(file_name, relative_path);
                        RealObjectSprite* bg_sprite = DEBUG_NEW RealObjectSprite();
                        bg_sprite->QuickSet(texture, bg_object, 0, 0, 1, 1);
                        if(bg_object->get_render_component()) bg_object->get_render_component()->ChangeSprite(bg_sprite);
                        bg_object->set_group_type(GROUP_TYPE::BACKGROUND2);
                        bg_object->set_pos(Vector2{ texture->get_width(), texture->get_height() } / 2.f);
                        bg_object->set_scale(Vector2{ texture->get_width(), texture->get_height() });
                        EnableMenuItem(hMenu, IDM_REMOVE_BACKGROUND_LAYER2, MF_ENABLED);
                    }
                }

            } break;
            case IDM_REMOVE_BACKGROUND_LAYER2: {
                GObject* bg_object;
                const std::vector<GObject*> objs = SceneManager::GetInstance()->get_current_scene()->GetGroupObjects(GROUP_TYPE::BACKGROUND2);
                if (!objs.empty()) {
                    SceneManager::GetInstance()->get_current_scene()->DeleteGroupObjects(GROUP_TYPE::BACKGROUND2);
                }
                EnableMenuItem(hMenu, IDM_REMOVE_BACKGROUND_LAYER2, MF_DISABLED);
            }
                                             break;
            case IDM_LOAD_BACKGROUND_LAYER3:{
                Scene_Tool* current_scene = dynamic_cast<Scene_Tool*>(SceneManager::GetInstance()->get_current_scene());
                if (current_scene) {
                    TCHAR file_path[256] = _T("");
                    TCHAR initial_path[256];
                    _tcscpy_s(initial_path, (PathManager::GetInstance()->GetContentPath()).c_str());

                    OPENFILENAME ofn = {};
                    memset(&ofn, 0, sizeof(OPENFILENAME));
                    ofn.lStructSize = sizeof(OPENFILENAME);
                    ofn.hwndOwner = hWnd;
                    ofn.lpstrFilter = _T("PNG\0*.png\0");
                    ofn.lpstrFile = file_path;
                    ofn.nMaxFile = 256;
                    ofn.lpstrInitialDir = initial_path;

                    if (GetOpenFileName(&ofn)) {
                        //1. 텍스쳐를 content\texture 폴더로 복사하기
                        TCHAR file_name[256] = _T("");
                        for (int i = static_cast<int>(_tcsclen(file_path)) - 1; i >= 0; i--) {
                            if (file_path[i] == _T('\\')) {
                                _tcscpy_s(file_name, &file_path[i + 1]);
                                break;
                            }
                        }
                        TCHAR relative_path[256] = _T("");
                        _tcscat_s(relative_path, _T("texture\\"));
                        _tcscat_s(relative_path, file_name);

                        TCHAR dest_path[256] = _T("");
                        _tcscat_s(dest_path, (PathManager::GetInstance()->GetContentPath()).c_str());
                        _tcscat_s(dest_path, relative_path);
                        CopyFile(file_path, dest_path, true);
                        //2. 복사한 텍스쳐를 불러와서, 이 텍스쳐를 1x1 스프라이트로 가지는 BACKGROUND 오브젝트 생성.
                        //이미 BACKGROUND 오브젝트가 있다면 스프라이트만 교체
                        Background* bg_object;
                        const std::vector<GObject*> objs = SceneManager::GetInstance()->get_current_scene()->GetGroupObjects(GROUP_TYPE::BACKGROUND3);
                        if (objs.empty()) {
                            bg_object = DEBUG_NEW Background();
                            CreateGObject(bg_object, GROUP_TYPE::BACKGROUND3);
                        }
                        else bg_object = dynamic_cast<Background*>(objs[0]);
                        Texture* texture = ResManager::GetInstance()->LoadTexture(file_name, relative_path);
                        RealObjectSprite* bg_sprite = DEBUG_NEW RealObjectSprite();
                        bg_sprite->QuickSet(texture, bg_object, 0, 0, 1, 1);
                        if(bg_object->get_render_component()) bg_object->get_render_component()->ChangeSprite(bg_sprite);
                        bg_object->set_group_type(GROUP_TYPE::BACKGROUND3);
                        bg_object->set_pos(Vector2{ texture->get_width(), texture->get_height() } / 2.f);
                        bg_object->set_scale(Vector2{ texture->get_width(), texture->get_height() });
                        EnableMenuItem(hMenu, IDM_REMOVE_BACKGROUND, MF_ENABLED);
                    }
                }

            }break;
            case IDM_REMOVE_BACKGROUND_LAYER3: {
                GObject* bg_object;
                const std::vector<GObject*> objs = SceneManager::GetInstance()->get_current_scene()->GetGroupObjects(GROUP_TYPE::BACKGROUND3);
                if (!objs.empty()) {
                    SceneManager::GetInstance()->get_current_scene()->DeleteGroupObjects(GROUP_TYPE::BACKGROUND3);
                }
                EnableMenuItem(hMenu, IDM_REMOVE_BACKGROUND, MF_DISABLED);
            } break;
            case IDM_LOAD_TOPGROUND: {
                Scene_Tool* current_scene = dynamic_cast<Scene_Tool*>(SceneManager::GetInstance()->get_current_scene());
                if (current_scene) {
                    TCHAR file_path[256] = _T("");
                    TCHAR initial_path[256];
                    _tcscpy_s(initial_path, (PathManager::GetInstance()->GetContentPath()).c_str());

                    OPENFILENAME ofn = {};
                    memset(&ofn, 0, sizeof(OPENFILENAME));
                    ofn.lStructSize = sizeof(OPENFILENAME);
                    ofn.hwndOwner = hWnd;
                    ofn.lpstrFilter = _T("PNG\0*.png\0");
                    ofn.lpstrFile = file_path;
                    ofn.nMaxFile = 256;
                    ofn.lpstrInitialDir = initial_path;

                    if (GetOpenFileName(&ofn)) {
                        //1. 텍스쳐를 content\texture 폴더로 복사하기
                        TCHAR file_name[256] = _T("");
                        for (int i = static_cast<int>(_tcsclen(file_path)) - 1; i >= 0; i--) {
                            if (file_path[i] == _T('\\')) {
                                _tcscpy_s(file_name, &file_path[i + 1]);
                                break;
                            }
                        }
                        TCHAR relative_path[256] = _T("");
                        _tcscat_s(relative_path, _T("texture\\"));
                        _tcscat_s(relative_path, file_name);

                        TCHAR dest_path[256] = _T("");
                        _tcscat_s(dest_path, (PathManager::GetInstance()->GetContentPath()).c_str());
                        _tcscat_s(dest_path, relative_path);
                        CopyFile(file_path, dest_path, true);
                        //2. 복사한 텍스쳐를 불러와서, 이 텍스쳐를 1x1 스프라이트로 가지는 TOPGROUND 오브젝트 생성.
                        //이미 BACKGROUND 오브젝트가 있다면 스프라이트만 교체
                        Topground* bg_object;
                        const std::vector<GObject*> objs = SceneManager::GetInstance()->get_current_scene()->GetGroupObjects(GROUP_TYPE::TOPGROUND);
                        if (objs.empty()) {
                            bg_object = DEBUG_NEW Topground();
                            CreateGObject(bg_object, GROUP_TYPE::TOPGROUND);
                        }
                        else bg_object = dynamic_cast<Topground*>(objs[0]);
                        Texture* texture = ResManager::GetInstance()->LoadTexture(file_name, relative_path);
                        RealObjectSprite* bg_sprite = DEBUG_NEW RealObjectSprite();
                        bg_sprite->QuickSet(texture, bg_object, 0, 0, 1, 1);
                        if (bg_object->get_render_component()) bg_object->get_render_component()->ChangeSprite(bg_sprite);
                        bg_object->set_group_type(GROUP_TYPE::TOPGROUND);
                        bg_object->set_pos(Vector2{ texture->get_width(), texture->get_height() } / 2.f);
                        bg_object->set_scale(Vector2{ texture->get_width(), texture->get_height() });
                        EnableMenuItem(hMenu, IDM_REMOVE_TOPGROUND, MF_ENABLED);
                    }
                }

            }break;
            case IDM_REMOVE_TOPGROUND: {
                GObject* bg_object;
                const std::vector<GObject*> objs = SceneManager::GetInstance()->get_current_scene()->GetGroupObjects(GROUP_TYPE::TOPGROUND);
                if (!objs.empty()) {
                    SceneManager::GetInstance()->get_current_scene()->DeleteGroupObjects(GROUP_TYPE::TOPGROUND);
                }
                EnableMenuItem(hMenu, IDM_REMOVE_TOPGROUND, MF_DISABLED);
            } break;
            //===============================
            //  맵파일 관리
            //================================
            case IDM_LOAD_MAPFILE:{
                //BACKGROUND, TILE, INVISIBLEWALL을 .map 파일로 저장
                Scene_Tool* current_scene = dynamic_cast<Scene_Tool*>(SceneManager::GetInstance()->get_current_scene());
                //툴씬에서만 동작
                if (current_scene) {
                    TCHAR file_path[256] = _T("");
                    TCHAR initial_path[256];
                    _tcscpy_s(initial_path, (PathManager::GetInstance()->GetContentPath()).c_str());

                    OPENFILENAME ofn = {};
                    memset(&ofn, 0, sizeof(OPENFILENAME));
                    ofn.lStructSize = sizeof(OPENFILENAME);
                    ofn.hwndOwner = hWnd;
                    ofn.lpstrFilter = _T("MAP\0*.map\0");
                    ofn.lpstrFile = file_path;
                    ofn.nMaxFile = 256;
                    ofn.lpstrInitialDir = initial_path;

                    if (GetOpenFileName(&ofn)) {

                        //2. 복사한 맵을 불러와서, 이 맵으로 타일 리스트를 로드함.
                        //기존의 배경, 타일, 콜라이더는 전부 지워야함.
                        SceneManager::GetInstance()->get_current_scene()->DeleteGroupObjects(GROUP_TYPE::BACKGROUND1);
                        SceneManager::GetInstance()->get_current_scene()->DeleteGroupObjects(GROUP_TYPE::BACKGROUND2);
                        SceneManager::GetInstance()->get_current_scene()->DeleteGroupObjects(GROUP_TYPE::BACKGROUND3);
                        SceneManager::GetInstance()->get_current_scene()->DeleteGroupObjects(GROUP_TYPE::TOPGROUND);
                        SceneManager::GetInstance()->get_current_scene()->DeleteGroupObjects(GROUP_TYPE::TILE);
                        SceneManager::GetInstance()->get_current_scene()->DeleteGroupObjects(GROUP_TYPE::INVISIBLE_WALL);

                        FileManager::GetInstance()->LoadMap(file_path);
                        

                        

                    }
                }

            } break;
            case IDM_SAVE_MAPFILE: {
                //BACKGROUND, TILE, INVISIBLEWALL을 .map 파일로 저장
                Scene_Tool* current_scene = dynamic_cast<Scene_Tool*>(SceneManager::GetInstance()->get_current_scene());
                //툴씬에서만 동작

                if (current_scene) {
                    TCHAR file_path[256] = _T("");

                    OPENFILENAME ofn = {};
                    memset(&ofn, 0, sizeof(OPENFILENAME));
                    ofn.lStructSize = sizeof(OPENFILENAME);
                    ofn.hwndOwner = hWnd;
                    ofn.lpstrFilter = _T("Map File\0*.map\0");
                    ofn.lpstrFile = file_path;
                    ofn.nMaxFile = 256;


                    if (GetSaveFileName(&ofn)) {
                        if(_tcscmp(&file_path[_tcsclen(file_path)-4], _T(".map")))
                            _tcscat_s(file_path, _T(".map"));
                        FileManager::GetInstance()->SaveMap(file_path);

                    }
                }
            } break;
            case IDM_DELETE_MAP: {
                Scene_Tool* current_scene = dynamic_cast<Scene_Tool*>(SceneManager::GetInstance()->get_current_scene());
                if (current_scene) {
                    SceneManager::GetInstance()->get_current_scene()->DeleteGroupObjects(GROUP_TYPE::BACKGROUND1);
                    SceneManager::GetInstance()->get_current_scene()->DeleteGroupObjects(GROUP_TYPE::BACKGROUND2);
                    SceneManager::GetInstance()->get_current_scene()->DeleteGroupObjects(GROUP_TYPE::BACKGROUND3);
                    SceneManager::GetInstance()->get_current_scene()->DeleteGroupObjects(GROUP_TYPE::TOPGROUND);
                    SceneManager::GetInstance()->get_current_scene()->DeleteGroupObjects(GROUP_TYPE::TILE);
                    SceneManager::GetInstance()->get_current_scene()->DeleteGroupObjects(GROUP_TYPE::INVISIBLE_WALL);
                    
                    current_scene->CreateEmptyTilemap(current_scene->get_column_count(), current_scene->get_row_count());
                }
            } break;
            case IDM_SAVE_TILEMAP_TO_PNG: {
                Scene_Tool* current_scene = dynamic_cast<Scene_Tool*>(SceneManager::GetInstance()->get_current_scene());
                //툴씬에서만 동작
                if (current_scene) {

                    DXClass::GetInstance()->SaveMapfileToPng(current_scene->GetGroupObjects(GROUP_TYPE::TILE), Vector2{ current_scene->get_column_count() * TILE_WIDTH, current_scene->get_row_count() * TILE_HEIGHT });
                }
                break;
            } break;

            case IDM_EXIT:
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    break;
    case WM_SIZE:
    {
        Core::GetInstance()->SyncResolution();
    }

    break;
    case WM_GETMINMAXINFO :
    {
        //=====================
        // 해상도 변경 막기
        //=====================
        RECT resolution_rect{ 0, 0, 1024, 768 };
        AdjustWindowRect(&resolution_rect, WS_OVERLAPPEDWINDOW, TRUE);
        ((MINMAXINFO*)lParam)->ptMaxTrackSize = POINT{ resolution_rect.right - resolution_rect.left, resolution_rect.bottom - resolution_rect.top };
        ((MINMAXINFO*)lParam)->ptMinTrackSize = POINT{ resolution_rect.right - resolution_rect.left, resolution_rect.bottom - resolution_rect.top };
        break;
    }
    case WM_DESTROY: // WM_CLOSE -> WM_QUIT -> WM_DESTROY 순서로 발생
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


// 타일셀 크기 변경 메시지 처리기
INT_PTR CALLBACK ChangeTilecellSize(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;


    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK_BTN)
        {
            UINT x_size = GetDlgItemInt(hDlg, IDC_WIDTH_TF, nullptr, false);
            UINT y_size = GetDlgItemInt(hDlg, IDC_HEIGHT_TF, nullptr, false);
            Scene_Tool* current_scene = dynamic_cast<Scene_Tool*>(SceneManager::GetInstance()->get_current_scene());
            if (current_scene) {
                current_scene->CreateEmptyTilemap(x_size, y_size);
            }
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        else if (LOWORD(wParam) == IDCANCEL_BTN) {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
        
    }
    return (INT_PTR)FALSE;
}

// 타일 텍스쳐 변경 메시지 처리기
INT_PTR CALLBACK ChangeTileuisTexture(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;


    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK )
        {
            UINT tile_width_px = GetDlgItemInt(hDlg, IDC_TILEUIS_TILE_WIDTH_PX, nullptr, false);
            UINT tile_height_px = GetDlgItemInt(hDlg, IDC_TILEUIS_TILE_HEIGHT_PX, nullptr, false);
            UINT interval_x = GetDlgItemInt(hDlg, IDC_TILEUIS_TILE_INTERVAL_X, nullptr, false);
            UINT interval_y = GetDlgItemInt(hDlg, IDC_TILEUIS_TILE_INTERVAL_Y, nullptr, false);

            Scene_Tool* current_scene = dynamic_cast<Scene_Tool*>(SceneManager::GetInstance()->get_current_scene());
            if (current_scene) {
                //1. 텍스쳐 불러오기
                TCHAR file_path[256] = _T("");
                TCHAR initial_path[256];
                _tcscpy_s(initial_path, (PathManager::GetInstance()->GetContentPath()).c_str());

                OPENFILENAME ofn = {};
                memset(&ofn, 0, sizeof(OPENFILENAME));
                ofn.lStructSize = sizeof(OPENFILENAME);
                ofn.hwndOwner = Core::GetInstance()->get_main_hwnd();
                ofn.lpstrFilter = _T("PNG\0*.png\0");
                ofn.lpstrFile = file_path;
                ofn.nMaxFile = 256;
                ofn.lpstrInitialDir = initial_path;

                if (GetOpenFileName(&ofn)) {
                    //1. 텍스쳐를 content\texture 폴더로 복사하기
                    TCHAR file_name[256] = _T("");
                    for (int i = static_cast<int>(_tcsclen(file_path)) - 1; i >= 0; i--) {
                        if (file_path[i] == _T('\\')) {
                            _tcscpy_s(file_name, &file_path[i + 1]);
                            break;
                        }
                    }
                    TCHAR relative_path[256] = _T("");
                    _tcscat_s(relative_path, _T("texture\\"));
                    _tcscat_s(relative_path, file_name);

                    TCHAR dest_path[256] = _T("");
                    _tcscat_s(dest_path, (PathManager::GetInstance()->GetContentPath()).c_str());
                    _tcscat_s(dest_path, relative_path);
                    CopyFile(file_path, dest_path, true);

                    Texture* texture = ResManager::GetInstance()->LoadTexture(file_name, relative_path);
                    //2. Scene_Tool 함수 실행(tileeditui에도 영향을 줌)
                    current_scene->ChangeTileuisTexture(texture
                        , Vector2{ 0, 0 }
                        , Vector2{ texture->get_width(), texture->get_height() }
                        , Vector2{ tile_width_px, tile_height_px }
                        , Vector2{ interval_x, interval_y }
                        , (texture->get_width() * texture->get_height()) / (tile_width_px * tile_height_px));
                }
            }
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        else if (LOWORD(wParam) == IDCANCEL) {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;

    }
    return (INT_PTR)FALSE;
}


// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
