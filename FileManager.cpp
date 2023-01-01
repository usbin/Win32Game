#include "FileManager.h"
#include "SceneManager.h"
#include "Scene_Tool.h"
#include "Background.h"
#include "Tile.h"
#include "InvisibleWall.h"
#include "Core.h"
#include "resource.h"

FileManager::FileManager() {};
FileManager::~FileManager() {};
void FileManager::SaveMap(const tstring& file_path)
{
	FILE* p_file;
	_tfopen_s(&p_file, file_path.c_str(), _T("wb"));
	assert(p_file);

	//툴씬에서만 동작
	Scene_Tool* scene = dynamic_cast<Scene_Tool*>(SceneManager::GetInstance()->get_current_scene());
	if (scene == nullptr) return;

	const std::vector<GObject*>& bgs1 = scene->GetGroupObjects(GROUP_TYPE::BACKGROUND1);
	const std::vector<GObject*>& bgs2 = scene->GetGroupObjects(GROUP_TYPE::BACKGROUND2);
	const std::vector<GObject*>& bgs3 = scene->GetGroupObjects(GROUP_TYPE::BACKGROUND3);
	const std::vector<GObject*>& walls = scene->GetGroupObjects(GROUP_TYPE::INVISIBLE_WALL);
	

	//BACKGROUND는 레이어당 반드시 하나만 있음.
	//1. BACKGROUND 저장
	GObject* bg = bgs1.empty() ? nullptr : bgs1[0];
	fwrite(&bg, sizeof(DWORD_PTR), 1, p_file);
	if(bg){
		bg->SaveToFile(p_file);
	}
	GObject* bg2 = bgs2.empty() ? nullptr : bgs2[0];
	fwrite(&bg2, sizeof(DWORD_PTR), 1, p_file);
	if (bg2) {
		bg2->SaveToFile(p_file);
	}
	GObject* bg3 = bgs3.empty() ? nullptr : bgs3[0];
	fwrite(&bg3, sizeof(DWORD_PTR), 1, p_file);
	if (bg3) {
		bg3->SaveToFile(p_file);
	}
	//2. INVISIBLE_WALL 개수, INVISIBLE_WALL 저장
	UINT walls_size = walls.size();
	fwrite(&walls_size, sizeof(UINT), 1, p_file);
	for (int i = 0; i < walls.size(); i++) {
		walls[i]->SaveToFile(p_file);
	}

	fclose(p_file);
	

}

void FileManager::LoadMap(const tstring& file_path)
{

	HMENU hmenu = GetMenu(Core::GetInstance()->get_main_hwnd());

	EnableMenuItem(hmenu, IDM_REMOVE_BACKGROUND_LAYER1, MF_DISABLED);
	EnableMenuItem(hmenu, IDM_REMOVE_BACKGROUND_LAYER2, MF_DISABLED);
	EnableMenuItem(hmenu, IDM_REMOVE_BACKGROUND_LAYER3, MF_DISABLED);


	FILE* p_file;
	_tfopen_s(&p_file, file_path.c_str(), _T("rb"));
	if (!p_file) {
		return;
	}

	//BACKGROUND는 반드시 하나만 있음.
	//1. BACKGROUND 로드
	GObject* bg;
	fread(&bg, sizeof(DWORD_PTR), 1, p_file);
	if (bg) {
		bg = new Background();
		bg->LoadFromFile(p_file);
		CreateGObject(bg, GROUP_TYPE::BACKGROUND1);
		
		EnableMenuItem(hmenu, IDM_REMOVE_BACKGROUND_LAYER1, MF_ENABLED);

	}
	GObject* bg2;
	fread(&bg2, sizeof(DWORD_PTR), 1, p_file);
	if (bg2) {
		bg2 = new Background();
		bg2->LoadFromFile(p_file);
		CreateGObject(bg2, GROUP_TYPE::BACKGROUND2);
		EnableMenuItem(hmenu, IDM_REMOVE_BACKGROUND_LAYER2, MF_ENABLED);
	}
	GObject* bg3;
	fread(&bg3, sizeof(DWORD_PTR), 1, p_file);
	if (bg3) {
		bg3 = new Background();
		bg3->LoadFromFile(p_file);
		CreateGObject(bg3, GROUP_TYPE::BACKGROUND3);
		EnableMenuItem(hmenu, IDM_REMOVE_BACKGROUND_LAYER3, MF_ENABLED);
	}
	
	//2. Invisible Wall 로드
	UINT walls_size;
	fread(&walls_size, sizeof(UINT), 1, p_file);
	for (int i = 0; i < walls_size; i++) {
		InvisibleWall* wall = new InvisibleWall();
		wall->LoadFromFile(p_file);
		CreateGObject(wall, GROUP_TYPE::INVISIBLE_WALL);
	}

	fclose(p_file);


}

void FileManager::SaveWallFile(const tstring& file_path)
{
	//툴씬에서만 동작
	Scene_Tool* scene = dynamic_cast<Scene_Tool*>(SceneManager::GetInstance()->get_current_scene());
	if (scene == nullptr) return;

	FILE* p_file;
	_tfopen_s(&p_file, file_path.c_str(), _T("wb"));
	assert(p_file);

	const std::vector<GObject*>& walls = scene->GetGroupObjects(GROUP_TYPE::INVISIBLE_WALL);
	UINT walls_size = walls.size();
	fwrite(&walls_size, sizeof(UINT), 1, p_file);
	for (int i = 0; i < walls.size(); i++) {
		walls[i]->SaveToFile(p_file);
	}

	fclose(p_file);
}

void FileManager::LoadWallFile(const tstring& file_path)
{
	//툴씬에서만 동작
	Scene_Tool* scene = dynamic_cast<Scene_Tool*>(SceneManager::GetInstance()->get_current_scene());
	if (scene == nullptr) return;

	FILE* p_file;
	_tfopen_s(&p_file, file_path.c_str(), _T("rb"));
	if (!p_file) return;

	UINT walls_size;
	fread(&walls_size, sizeof(UINT), 1, p_file);
	for (int i = 0; i < walls_size; i++) {
		InvisibleWall* wall = new InvisibleWall();
		wall->LoadFromFile(p_file);
		CreateGObject(wall, GROUP_TYPE::INVISIBLE_WALL);
	}

	fclose(p_file);
}

void FileManager::SaveTilemapFile(const tstring& file_path)
{
	//툴씬에서만 동작
	Scene_Tool* scene = dynamic_cast<Scene_Tool*>(SceneManager::GetInstance()->get_current_scene());
	if (scene == nullptr) return;

	FILE* p_file;
	_tfopen_s(&p_file, file_path.c_str(), _T("wb"));
	assert(p_file);

	const std::vector<GObject*>& tiles = scene->GetGroupObjects(GROUP_TYPE::TILE);

	UINT tiles_size = tiles.size();
	fwrite(&tiles_size, sizeof(UINT), 1, p_file);
	for (int i = 0; i < tiles.size(); i++) {
		tiles[i]->SaveToFile(p_file);
	}
	fclose(p_file);
}

void FileManager::LoadTilemapFile(const tstring& file_path)
{
	FILE* p_file;
	_tfopen_s(&p_file, file_path.c_str(), _T("rb"));
	if (!p_file) return;

	UINT tiles_size;
	fread(&tiles_size, sizeof(UINT), 1, p_file);
	for (int i = 0; i < tiles_size; i++) {
		Tile* tile = new Tile();
		tile->LoadFromFile(p_file);
		CreateGObject(tile, GROUP_TYPE::TILE);

	}
	fclose(p_file);

}
